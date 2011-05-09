require_relative 'helper'

class TestConstants < MiniTest::Unit::TestCase
  def test_libssh_constant_defined
    assert defined?(LibSSH)
  end
end
