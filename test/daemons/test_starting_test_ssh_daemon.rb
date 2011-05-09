require_relative '../helper'

begin
  SSH.daemon.start
ensure
  SSH.daemon.stop
end
