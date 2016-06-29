##
## MaxMindDB Test
##

MaxMindDbDat = "/tmp/GeoLite2-City.mmdb"
IPAddr = '8.8.8.8'

assert("MaxMindDB#new") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  assert_not_equal(nil, maxminddb)
end

assert("MaxMindDB#lookup_string") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr
end

assert("MaxMindDB#country_code") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr
  assert_equal("US", maxminddb.country_code)
end

assert("MaxMindDB#region") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr

  assert_equal("CA", maxminddb.region)
end

assert("MaxMindDB#region_name") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr

  assert_equal("California", maxminddb.region_name)
end

assert("MaxMindDB#city") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr

  assert_equal("Mountain View", maxminddb.city)
end

assert("MaxMindDB#postal_code") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr

  assert_equal("94035", maxminddb.postal_code)
end

assert("MaxMindDB#latitude") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr

  assert_equal(37.386, maxminddb.latitude)
end

assert("MaxMindDB#longitude") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr

  assert_equal(-122.0838, maxminddb.longitude.round(4))
end

assert("MaxMindDB#metro_code") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr

  assert_equal(807, maxminddb.metro_code)
end

assert("MaxMindDB#time_zone") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string IPAddr

  assert_equal("America/Los_Angeles", maxminddb.time_zone)
end
