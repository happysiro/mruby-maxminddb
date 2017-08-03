/*
** mrb_maxminddb.c - Maxminddb class
**
** Copyright (c) Kenichi Mitsugi 2016
**
** See Copyright Notice in LICENSE
*/

#include <maxminddb.h>
#include "maxminddb-compat-util.h"

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_maxminddb.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  MMDB_s mmdb;
  MMDB_lookup_result_s lookup_result_s;
  int mmdb_lookup_error;
  int gai_error;
  char *db;
  char *host;
  char *str;
} mrb_maxminddb_data;

static void mrb_maxminddb_free(mrb_state *mrb, void *p) {
  mrb_maxminddb_data *data = p;
  MMDB_close(&(data->mmdb));
}

static const struct mrb_data_type mrb_maxminddb_data_type = {
    "mrb_maxminddb_data", mrb_maxminddb_free,
};

static mrb_value mrb_maxminddb_init(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data;
  char *db;

  data = (mrb_maxminddb_data *)DATA_PTR(self);

  if (data) {
    mrb_free(mrb, data);
  }

  DATA_TYPE(self) = &mrb_maxminddb_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "z", &db);

  data = (mrb_maxminddb_data *)mrb_malloc(mrb, sizeof(mrb_maxminddb_data));
  data->mmdb_lookup_error = -1;
  data->gai_error = -1;
  data->db = db;

  int status = MMDB_open(data->db, MMDB_MODE_MMAP, &(data->mmdb));

  if (MMDB_SUCCESS != status) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Open Error");
  }

  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_maxminddb_lookup_string(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  char *ipaddr = NULL;

  mrb_get_args(mrb, "z", &ipaddr);
  data->host = ipaddr;

  data->lookup_result_s =
      MMDB_lookup_string(&(data->mmdb), data->host, &(data->gai_error),
                         &(data->mmdb_lookup_error));

  if (0 != data->gai_error) {
    mrb_raise(mrb, E_RUNTIME_ERROR, gai_strerror(data->gai_error));
  }

  if (MMDB_SUCCESS != data->mmdb_lookup_error) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Lookup Error");
  }

  return self;
}

static mrb_value mrb_maxminddb_country_code(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  const char *path[3] = {"country", "iso_code", NULL};

  if (0 != data->gai_error && MMDB_SUCCESS != data->mmdb_lookup_error)
    mrb_raise(mrb, E_RUNTIME_ERROR, "call lookup_string");

  MMDB_entry_data_s entry_data;
  int status =
      MMDB_aget_value(&(data->lookup_result_s.entry), &entry_data, path);

  if (MMDB_SUCCESS != status)
    mrb_raise(mrb, E_RUNTIME_ERROR, "MMDB_aget_value error");

  return mrb_str_new_cstr(
      mrb, mmdb_strndup((char *)entry_data.utf8_string, entry_data.data_size));
}

static mrb_value mrb_maxminddb_region(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  const char *path[4] = {"subdivisions", "0", "iso_code", NULL};

  if (0 != data->gai_error && MMDB_SUCCESS != data->mmdb_lookup_error)
    mrb_raise(mrb, E_RUNTIME_ERROR, "call lookup_string");

  MMDB_entry_data_s entry_data;
  int status =
      MMDB_aget_value(&(data->lookup_result_s.entry), &entry_data, path);

  if (MMDB_SUCCESS != status)
    return mrb_nil_value();

  return mrb_str_new_cstr(
      mrb, mmdb_strndup((char *)entry_data.utf8_string, entry_data.data_size));
}

static mrb_value mrb_maxminddb_region_name(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  const char *path[5] = {"subdivisions", "0", "names", "en", NULL};

  if (0 != data->gai_error && MMDB_SUCCESS != data->mmdb_lookup_error)
    mrb_raise(mrb, E_RUNTIME_ERROR, "call lookup_string");

  MMDB_entry_data_s entry_data;
  int status =
      MMDB_aget_value(&(data->lookup_result_s.entry), &entry_data, path);

  if (MMDB_SUCCESS != status)
    return mrb_nil_value();

  return mrb_str_new_cstr(
      mrb, mmdb_strndup((char *)entry_data.utf8_string, entry_data.data_size));
}

static mrb_value mrb_maxminddb_city(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  const char *path[4] = {"city", "names", "en", NULL};

  if (0 != data->gai_error && MMDB_SUCCESS != data->mmdb_lookup_error)
    mrb_raise(mrb, E_RUNTIME_ERROR, "call lookup_string");

  MMDB_entry_data_s entry_data;
  int status =
      MMDB_aget_value(&(data->lookup_result_s.entry), &entry_data, path);

  if (MMDB_SUCCESS != status)
    return mrb_nil_value();

  return mrb_str_new_cstr(
      mrb, mmdb_strndup((char *)entry_data.utf8_string, entry_data.data_size));
}

static mrb_value mrb_maxminddb_postal_code(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  const char *path[3] = {"postal", "code", NULL};

  if (0 != data->gai_error && MMDB_SUCCESS != data->mmdb_lookup_error)
    mrb_raise(mrb, E_RUNTIME_ERROR, "call lookup_string");

  MMDB_entry_data_s entry_data;
  int status =
      MMDB_aget_value(&(data->lookup_result_s.entry), &entry_data, path);

  if (MMDB_SUCCESS != status)
    return mrb_nil_value();

  return mrb_str_new_cstr(
      mrb, mmdb_strndup((char *)entry_data.utf8_string, entry_data.data_size));
}

static mrb_value mrb_maxminddb_latitude(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  const char *path[3] = {"location", "latitude", NULL};

  if (0 != data->gai_error && MMDB_SUCCESS != data->mmdb_lookup_error)
    mrb_raise(mrb, E_RUNTIME_ERROR, "call lookup_string");

  MMDB_entry_data_s entry_data;
  int status =
      MMDB_aget_value(&(data->lookup_result_s.entry), &entry_data, path);

  if (MMDB_SUCCESS != status)
    mrb_raise(mrb, E_RUNTIME_ERROR, "MMDB_aget_value error");

  return mrb_float_value(mrb, entry_data.double_value);
}

static mrb_value mrb_maxminddb_longitude(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  const char *path[3] = {"location", "longitude", NULL};

  if (0 != data->gai_error && MMDB_SUCCESS != data->mmdb_lookup_error)
    mrb_raise(mrb, E_RUNTIME_ERROR, "call lookup_string");

  MMDB_entry_data_s entry_data;
  int status =
      MMDB_aget_value(&(data->lookup_result_s.entry), &entry_data, path);

  if (MMDB_SUCCESS != status)
    mrb_raise(mrb, E_RUNTIME_ERROR, "MMDB_aget_value error");

  return mrb_float_value(mrb, entry_data.double_value);
}

static mrb_value mrb_maxminddb_metro_code(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  const char *path[3] = {"location", "metro_code", NULL};

  if (0 != data->gai_error && MMDB_SUCCESS != data->mmdb_lookup_error)
    mrb_raise(mrb, E_RUNTIME_ERROR, "call lookup_string");

  MMDB_entry_data_s entry_data;
  int status =
      MMDB_aget_value(&(data->lookup_result_s.entry), &entry_data, path);

  if (MMDB_SUCCESS != status)
    return mrb_nil_value();

  return mrb_fixnum_value(entry_data.uint16);
}

static mrb_value mrb_maxminddb_time_zone(mrb_state *mrb, mrb_value self) {
  mrb_maxminddb_data *data = DATA_PTR(self);
  const char *path[3] = {"location", "time_zone", NULL};

  if (0 != data->gai_error && MMDB_SUCCESS != data->mmdb_lookup_error)
    mrb_raise(mrb, E_RUNTIME_ERROR, "call lookup_string");

  MMDB_entry_data_s entry_data;
  int status =
      MMDB_aget_value(&(data->lookup_result_s.entry), &entry_data, path);

  if (MMDB_SUCCESS != status)
    return mrb_nil_value();

  return mrb_str_new_cstr(
      mrb, mmdb_strndup((char *)entry_data.utf8_string, entry_data.data_size));
}

void mrb_mruby_maxminddb_gem_init(mrb_state *mrb) {
  struct RClass *maxminddb;
  maxminddb = mrb_define_class(mrb, "MaxMindDB", mrb->object_class);
  mrb_define_method(mrb, maxminddb, "initialize", mrb_maxminddb_init,
                    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, maxminddb, "lookup_string",
                    mrb_maxminddb_lookup_string, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, maxminddb, "country_code", mrb_maxminddb_country_code,
                    MRB_ARGS_NONE());
  mrb_define_method(mrb, maxminddb, "region", mrb_maxminddb_region,
                    MRB_ARGS_NONE());
  mrb_define_method(mrb, maxminddb, "region_name", mrb_maxminddb_region_name,
                    MRB_ARGS_NONE());
  mrb_define_method(mrb, maxminddb, "city", mrb_maxminddb_city,
                    MRB_ARGS_NONE());
  mrb_define_method(mrb, maxminddb, "postal_code", mrb_maxminddb_postal_code,
                    MRB_ARGS_NONE());
  mrb_define_method(mrb, maxminddb, "latitude", mrb_maxminddb_latitude,
                    MRB_ARGS_NONE());
  mrb_define_method(mrb, maxminddb, "longitude", mrb_maxminddb_longitude,
                    MRB_ARGS_NONE());
  mrb_define_method(mrb, maxminddb, "metro_code", mrb_maxminddb_metro_code,
                    MRB_ARGS_NONE());
  mrb_define_method(mrb, maxminddb, "time_zone", mrb_maxminddb_time_zone,
                    MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_maxminddb_gem_final(mrb_state *mrb) {}
