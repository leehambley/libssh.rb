require_relative 'helper'

class TestConnections < MiniTest::Unit::TestCase

  def test_libssh_connection_requires_at_least_one_argument
    assert_raises ArgumentError do
      LibSSH.connect
    end
  end

  #
  # The connection is not actually opened until
  # you try to do something which requires authentication
  #
  def test_should_report_not_connected_when_new
    c = LibSSH.connect 'hostname'
    assert (not c.connected?)
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

  def test_libssh_connection_should_accept_a_hash_for_a_port_param
    c = LibSSH.connect 'hostname', :port => 2234
    assert_equal 2234, c.port
  end

end
