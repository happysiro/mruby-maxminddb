/*
** mrb_maxminddb.c - Maxminddb class
**
** Copyright (c) Kenichi Mitsugi 2016
**
** See Copyright Notice in LICENSE
*/

#include <maxminddb.h>

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_maxminddb.h"
#include "maxminddb-compat-util.h"

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

static const struct mrb_data_type mrb_maxminddb_data_type = {
  "mrb_maxminddb_data", mrb_free,
};

static mrb_value mrb_maxminddb_init(mrb_state *mrb, mrb_value self)
{
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

static mrb_value mrb_maxminddb_lookup_string (mrb_state *mrb, mrb_value self)
{
  mrb_maxminddb_data *data = DATA_PTR(self);
  char *ipaddr = NULL;

  mrb_get_args(mrb, "z", &ipaddr);
  data->host = ipaddr;

  data->lookup_result_s = MMDB_lookup_string(&(data->mmdb), data->host, &(data->gai_error), &(data->mmdb_lookup_error));

  if (0 != data->gai_error) {
    mrb_raise(mrb, E_RUNTIME_ERROR, gai_strerror(data->gai_error));
  }

  if (MMDB_SUCCESS != data->mmdb_lookup_error) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Lookup Error");
  }

  return self;
}

static mrb_value mrb_maxminddb_country_code (mrb_state *mrb, mrb_value self)
{
  mrb_maxminddb_data *data = DATA_PTR(self);

  const char *path[3] = {
          "country",
          "iso_code",
          NULL
  };

  if (0 != data->gai_error) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Gai Error");
    mrb_raise(mrb, E_RUNTIME_ERROR, gai_strerror(data->gai_error));
  }

  if (MMDB_SUCCESS != data->mmdb_lookup_error) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Lookup Error");
  }

  MMDB_entry_data_s entry_data;
  MMDB_lookup_result_s result = data->lookup_result_s;

  int status = MMDB_aget_value(&result.entry, &entry_data, path);

  char *string = mmdb_strndup((char *)entry_data.utf8_string, entry_data.data_size);

  return mrb_str_new_cstr(mrb, string);
}

void mrb_mruby_maxminddb_gem_init(mrb_state *mrb)
{
    struct RClass *maxminddb;
    maxminddb = mrb_define_class(mrb, "MaxMindDB", mrb->object_class);
    mrb_define_method(mrb, maxminddb, "initialize", mrb_maxminddb_init, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, maxminddb, "lookup_string", mrb_maxminddb_lookup_string, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, maxminddb, "country_code", mrb_maxminddb_country_code, MRB_ARGS_NONE());
    DONE;
}

void mrb_mruby_maxminddb_gem_final(mrb_state *mrb)
{
}
