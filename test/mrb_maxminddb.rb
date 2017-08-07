##
## MaxMindDB Test
##

MaxMindDbDat = File.expand_path("../mruby-maxminddb/test/fixtures/GeoLite2-City.mmdb")

FullDataExpect = {
  :ip_addr      => "9.9.9.9",
  :country_code => "US",
  :region       => "NC",
  :region_name  => "North Carolina",
  :city         => "Durham",
  :postal_code  => "27709",
  :latitude     => 35.9940,
  :longitude    => -78.8986,
  :metro_code   => 560,
  :time_zone    => "America/New_York",
}

PoorDataExpect = {
  :ip_addr      => "74.122.8.1",
  :country_code => nil,
  :region       => nil,
  :region_name  => nil,
  :city         => nil,
  :postal_code  => nil,
  :latitude     => nil,
  :longitude    => nil,
  :metro_code   => nil,
  :time_zone    => nil,
}

assert("MaxMindDB#new") do
  maxminddb = MaxMindDB.new MaxMindDbDat
  assert_not_equal(nil, maxminddb)
end

assert("MaxMindDB#lookup_string") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  maxminddb.lookup_string PoorDataExpect[:ip_addr]
end

assert("MaxMindDB#country_code") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  assert_equal(FullDataExpect[:country_code], maxminddb.country_code)

  maxminddb.lookup_string PoorDataExpect[:ip_addr]
  assert_equal(PoorDataExpect[:country_code], maxminddb.country_code)
end

assert("MaxMindDB#region") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  assert_equal(FullDataExpect[:region], maxminddb.region)

  maxminddb.lookup_string PoorDataExpect[:ip_addr]
  assert_equal(PoorDataExpect[:region], maxminddb.region)
end

assert("MaxMindDB#region_name") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  assert_equal(FullDataExpect[:region_name], maxminddb.region_name)

  maxminddb.lookup_string PoorDataExpect[:ip_addr]
  assert_equal(PoorDataExpect[:region_name], maxminddb.region_name)
end

assert("MaxMindDB#city") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  assert_equal(FullDataExpect[:city], maxminddb.city)

  maxminddb.lookup_string PoorDataExpect[:ip_addr]
  assert_equal(PoorDataExpect[:city], maxminddb.city)
end

assert("MaxMindDB#postal_code") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  assert_equal(FullDataExpect[:postal_code], maxminddb.postal_code)

  maxminddb.lookup_string PoorDataExpect[:ip_addr]
  assert_equal(PoorDataExpect[:postal_code], maxminddb.postal_code)
end

assert("MaxMindDB#latitude") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  assert_equal(FullDataExpect[:latitude], maxminddb.latitude)

  maxminddb.lookup_string PoorDataExpect[:ip_addr]
  assert_equal(PoorDataExpect[:latitude], maxminddb.latitude)
end

assert("MaxMindDB#longitude") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  assert_equal(FullDataExpect[:longitude], maxminddb.longitude.round(4))

  maxminddb.lookup_string PoorDataExpect[:ip_addr]
  assert_equal(PoorDataExpect[:longitude], maxminddb.longitude)
end

assert("MaxMindDB#metro_code") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  assert_equal(FullDataExpect[:metro_code], maxminddb.metro_code)

  maxminddb.lookup_string PoorDataExpect[:ip_addr]
  assert_equal(PoorDataExpect[:metro_code], maxminddb.metro_code)
end

assert("MaxMindDB#time_zone") do
  maxminddb = MaxMindDB.new MaxMindDbDat

  maxminddb.lookup_string FullDataExpect[:ip_addr]
  assert_equal(FullDataExpect[:time_zone], maxminddb.time_zone)

  maxminddb.lookup_string PoorDataExpect[:ip_addr]
  assert_equal(PoorDataExpect[:time_zone], maxminddb.time_zone)
end
