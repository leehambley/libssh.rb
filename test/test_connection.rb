require_relative 'helper'

class TestConnections < MiniTest::Unit::TestCase

  def test_libssh_connection_requires_at_least_one_argument
    assert_raises ArgumentError do
      LibSSH.connect
    end
  end

  def test_libssh_connection_should_accept_one_argument_and_assign_it_to_hostname
    assert_silent do
      LibSSH.connect 'hostname'
    end
  end

end
