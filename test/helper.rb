require "rubygems"
require "bundler/setup"

require 'erb'
require 'minitest/unit'
require 'minitest/autorun'

require File.join(Dir.pwd, 'test/support/string')
require File.join(Dir.pwd, 'test/support/ssh_daemon')
