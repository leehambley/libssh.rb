class String
  def process_erb
    ERB.new(self).result(binding).gsub(/^\s+/, '')
  end
end

