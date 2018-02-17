MRuby::Gem::Specification.new('mruby-maxminddb') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Kenichi Mitsugi'
  spec.add_test_dependency 'mruby-io', :mgem => 'mruby-io'

  def maxminddb_origin_path
    if File.exist?("../test/fixtures/GeoLite2-City.mmdb.gz")
      "#{build.build_dir}/../../../test/fixtures/GeoLite2-City.mmdb"
    else
      "#{build.build_dir}/../mrbgems/mruby-maxminddb/test/fixtures/GeoLite2-City.mmdb"
    end
  end

  maxminddb_ci_path = "#{build.build_dir}/../maxminddb-fixtures/GeoLite2-City.mmdb"

  sh "mkdir -p #{File.dirname maxminddb_ci_path}"
  sh "gzip -cd #{maxminddb_origin_path}.gz > #{maxminddb_ci_path}" unless File.exist?(maxminddb_ci_path)
end
