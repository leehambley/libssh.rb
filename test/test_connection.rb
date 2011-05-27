require_relative 'helper'

class TestConnections < MiniTest::Unit::TestCase

  def test_libssh_connection_requires_at_least_one_argument
    assert_raises ArgumentError do
      LibSSH.connect
    end
  end

  def test_libssh_connection_should_accept_one_argument_and_assign_it_to_hostname
    c = nil
    assert_silent do
      c = LibSSH.connect 'hostname'
    end
    assert c
    assert c.respond_to?(:hostname)
    assert_equal 'hostname',  c.hostname
  end

end
