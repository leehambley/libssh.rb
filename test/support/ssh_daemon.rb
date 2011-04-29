require 'forwardable'

class SSHDaemon

  class << self

    extend SingleForwardable


    def_delegator :daemon, :start,    :start
    def_delegator :daemon, :stop,     :stop
    def_delegator :daemon, :running?, :running?

    private
      def daemon
        DaemonController.new(
          :identifier     => "Test SSH Server",
          :start_command  => "sshd -f #{configuration_filename}",
          :ping_command   => lambda { TCPSocket.new('localhost', 2234) },
          :pid_file       => pid_file
        )
      end
      def write_configuration_file
        File.open(configuration_filename, "w") do |file|
          file.write default_configuration.process_erb
        end
      end
      def configuration_filename
        File.join(Dir.pwd, %w(test tmp config sshd_default.conf))
      end
      def default_configuration
        <<-EOB
          Port 2234
          ListenAddress ::
          ListenAddress 0.0.0.0
          Protocol 2
          StrictModes yes
          PasswordAuthentication yes
          ChrootDirectory <%= chroot %>
          PidFile <%= pidfile %>
        EOB
      end
      def chroot
        File.join(Dir.pwd, %w(test tmp sandbox))
      end
      def pid_file
        File.join(Dir.pwd, %w(test pids sshd.pid))
      end
  end
end

