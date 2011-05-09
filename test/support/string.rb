class String
  def process_erb(world_binding = binding)
    ERB.new(self).result(world_binding).gsub(/^\s+/, '')
  end
end

