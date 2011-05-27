require 'libsshrb'

module LibSSH

  def self.connect(*args)
    Connection.new(*args)
  end

end
