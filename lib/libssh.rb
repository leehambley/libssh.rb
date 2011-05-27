require 'libsshrb'

module LibSSH

  Error           = Class.new(StandardError)
  ConnectionError = Class.new(LibSSH::Error)

  def self.connect(*args)
    Connection.new(*args)
  end

  class Connection
    def initialize(*args)
      raise ConnectionError
    end
  end


end
