#!/usr/bin/ruby

require 'fileutils'

Dir.glob("*/target").each do | target |
	FileUtils.rm_rf(target, {:verbose => true})
end