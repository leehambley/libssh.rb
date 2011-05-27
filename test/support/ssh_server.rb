require 'fileutils'
require 'daemon_controller'

class SSH
  class << self

    def daemon
      DaemonController.new(
        :identifier     => "Test SSH Server",
        :start_command  => "#{sshd} -f #{configuration_filename} -h #{hostkey_filename} -e  2> #{log_filename}",
        :ping_command   => lambda { TCPSocket.new('localhost', 2234) },
        :pid_file       => pid_file,
        :log_file       => log_filename
      )
    end

    def write_configurations
      write_configuration_file! unless File.exists?(configuration_filename)
      write_hostkey_file!       unless File.exists?(hostkey_filename)
    end

    def write_configurations!
      File.unlink configuration_filename
      File.unlink hostkey_filename
      write_configurations
    end

    private
      def sshd
        `which sshd`.chomp
      end
      def write_configuration_file!
        File.open(configuration_filename, "w") do |file|
          file.write default_configuration.process_erb(binding)
        end
      end
      def log_filename
        File.join(Dir.pwd, %w(test tmp log sshd-error.log))
      end
      def hostkey_filename
        File.join(Dir.pwd, %w(test tmp config sshd_hostkey))
      end
      def write_hostkey_file!
        `echo 'Y' | ssh-keygen -b 1024 -f #{hostkey_filename} -N ''`
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
          PidFile <%= pid_file %>
          LogLevel INFO
        EOB
      end
      def chroot
        File.join(Dir.pwd, %w(test tmp sandbox))
      end
      def pid_file
        pid = File.join(Dir.pwd, %w(test tmp pids sshd.pid))
        FileUtils.mkdir_p(File.dirname(pid))
        pid
      end
  end
end

