require 'libsshrb'

module LibSSH

  def self.connect(hostname, options = {})
    Connection.new(hostname, options)
  end

end
