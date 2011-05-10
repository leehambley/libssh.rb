require "rubygems"
require "bundler/setup"

require 'erb'
require 'ruby-debug'
require 'minitest/unit'
require 'minitest/autorun'

require 'libssh'

require_relative 'support/string'
require_relative 'support/ssh_server'
