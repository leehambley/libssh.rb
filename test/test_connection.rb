require_relative 'helper'

class TestConnections < MiniTest::Unit::TestCase

  def test_libssh_connection_fails_with_no_server_running
    assert_raises LibSSH::ConnectionError do
      LibSSH.connect 'localhost', :port => ''
    end
  end

end
