# Usage:
#   [sudo] gem install mechanize
#   ruby tumblr-photo-ripper.rb

$stdout.sync = true	# flush after every puts

require 'rubygems'
require 'mechanize'

# Your Tumblr subdomain, e.g. "jamiew" for "jamiew.tumblr.com"
site = "rustbucket2-0"
site = ARGV[0]

puts "START ----- site: #{site}"

FileUtils.mkdir_p(site)

concurrency = 8
num = 50
start = 0

def handleimgurls(image_urls, concurrency, site)
  image_urls.each_slice(concurrency).each do |group|
    threads = []
    group.each do |url|
      threads << Thread.new {
        # puts "Saving photo #{url}"
        begin
			file = Mechanize.new.get(url)
			filename = File.basename(file.uri.to_s.split('?')[0])
			if !File.exist?("#{site}/#{filename}")
				file.save_as("#{site}/#{filename}")
				#puts "Saving photo #{url} > #{site}/#{filename}"
			end
        rescue Mechanize::ResponseCodeError
          puts "Error getting file, #{$!}"
        end
      }
    end
    threads.each{|t| t.join }
  end
end

loop do
  puts "start=#{start}"

  url = "http://#{site}.tumblr.com/api/read?type=photo&num=#{num}&start=#{start}"
  page = Mechanize.new.get(url)
  doc = Nokogiri::XML.parse(page.body)

  images = (doc/'post photo-url').select{|x| x if x['max-width'].to_i == 1280 }
  image_urls = images.map {|x| x.content }
  handleimgurls(image_urls, concurrency, site)

  didVersion2 = false
  
  #version 2
  if images.count == 0
	image_urls = page.body.scan(/&lt;img src=\"(.*?)\"/).flatten
	handleimgurls(image_urls, concurrency, site)
	num = image_urls.length()
	images = image_urls
	didVersion2 = true
  end
  
  puts "#{images.count} images found (num=#{num})"
  
  if images.count < num || start > 100000
    puts "END ----- (start: #{start}) version2: #{didVersion2} site: #{site}\n"
    break
  else
    start += num
	puts "do next page. start: #{start}  version2: #{didVersion2}"
  end

end
