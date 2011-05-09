require_relative '../helper'

class TestStartingSSHServer < MiniTest::Unit::TestCase

  def setup
    SSH.daemon.start
  end

  def teardown
    SSH.daemon.stop
  end

  def test_ssh_daemon_connectable
    assert SSH.daemon.running?
  end

end
