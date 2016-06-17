##
## Maxminddb Test
##

assert("Maxminddb#hello") do
  t = Maxminddb.new "hello"
  assert_equal("hello", t.hello)
end

assert("Maxminddb#bye") do
  t = Maxminddb.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Maxminddb.hi") do
  assert_equal("hi!!", Maxminddb.hi)
end
