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
p Maxminddb.hi
#=> "hi!!"
t = Maxminddb.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
