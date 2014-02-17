
require 'nokogiri'
require './fns'

filename = ARGV[0]
xml = Nokogiri::XML(open(filename))

xml.xpath('//tile').each do |tile|
  gid = tile.get_attribute('gid').to_i
  tile.set_attribute('gid', convert2new(gid).to_s)
end

tileset = xml.xpath('//tileset/image')[0]
tileset.set_attribute('width', '2048')
tileset.set_attribute('height', '2016')

f = File.open(filename, 'w')
f.write(xml.to_xml)
f.close

