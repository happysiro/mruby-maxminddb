##
## MaxMindDB Test
##

MaxMindDbDat = "/tmp/GeoLite2-City.mmdb"

Data1 = {
  :ip_addr      => "8.8.8.8",
  :country_code => "US",
  :region       => nil,
  :region_name  => nil,
  :city         => nil,
  :postal_code  => nil,
  :latitude     => 37.751000,
  :longitude    => -97.822000,
  :metro_code   => nil,
  :time_zone    => nil,
}

Data2 = {
  :ip_addr      => "1.1.1.1",
  :country_code => "OC",
  :region       => "VIC",
  :region_name  => "Victoria",
  :city         => "Research",
  :postal_code  => "3095",
  :latitude     => -37.700000,
  :longitude    => 145.183300,
  :metro_code   => nil,
  :time_zone    => "Australia/Melbourne",
}

assert("MaxMindDB#new") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  assert_not_equal(nil, maxminddb)
end

assert("MaxMindDB#lookup_string") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]
end

assert("MaxMindDB#country_code") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]
  assert_equal(Data1[:country_code], maxminddb.country_code)
end

assert("MaxMindDB#region") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]

  assert_equal(Data1[:region], maxminddb.region)
end

assert("MaxMindDB#region_name") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]

  assert_equal(Data1[:region_name], maxminddb.region_name)
end

assert("MaxMindDB#city") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]

  assert_equal(Data1[:city], maxminddb.city) # => nil

  maxminddb.lookup_string Data2[:ip_addr]
  assert_equal(Data2[:city], maxminddb.city)
end

assert("MaxMindDB#postal_code") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]

  assert_equal(Data1[:postal_code], maxminddb.postal_code) # => nil
end

assert("MaxMindDB#latitude") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]

  assert_equal(Data1[:latitude], maxminddb.latitude)
end

assert("MaxMindDB#longitude") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]

  assert_equal(Data1[:longitude], maxminddb.longitude.round(4))
end

assert("MaxMindDB#metro_code") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]

  assert_equal(Data1['metro_code'], maxminddb.metro_code)
end

assert("MaxMindDB#time_zone") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  maxminddb.lookup_string Data1[:ip_addr]

  assert_equal(Data1[:time_zone], maxminddb.time_zone) # => nil

  maxminddb.lookup_string Data2[:ip_addr]
  assert_equal(Data2[:time_zone], maxminddb.time_zone)
end
