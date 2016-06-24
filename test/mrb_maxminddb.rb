##
## MaxMindDB Test
##

MaxMindDbDat = "/tmp/GeoIP/GeoLite2-City.mmdb"
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
