# mruby-maxminddb   [![Build Status](https://travis-ci.org/happysiro/mruby-maxminddb.svg?branch=master)](https://travis-ci.org/happysiro/mruby-maxminddb)
Maxminddb class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'happysiro/mruby-maxminddb'
end
```
## example
```ruby
MaxMindDbDat = "/tmp/GeoLite2-City.mmdb"
IPAddr = '8.8.8.8'

maxminddb = MaxMindDB.new MaxMindDbDat

maxminddb.lookup_string IPAddr

maxminddb.country_code       #=> US
maxminddb.region             #=> CA
maxminddb.region_name        #=> California
maxminddb.city               #=> Mountain View
maxminddb.postal_code        #=> 94035
maxminddb.latitude           #=> 37.386
maxminddb.longitude.round(4) #=> -122.0838
maxminddb.metro_code         #=> 807
maxminddb.time_zone          #=> America/Los_Angeles

```

## License
under the MIT License:
- see LICENSE file
