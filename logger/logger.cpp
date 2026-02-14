void	Logger::create_log(const std::string& filename) const
{
	std::ofstream	file(filename);

	if (!file.is_open())
	{
		std::cerr << "Error: unable to open " << filename << "\n";
		return ;
	}
	file << "   A  B   C  D   E  F   G  H\n";
	file << " +---------------------------+\n";
	for (int i = 0; i < 8; ++i)
	{
		file << i + 1 << "|";
		for (int j = 0; j < 8; ++j)
		{
			if (j < 7)
			{
				if ((i + j + 1) % 2 == 0)
					file << u8"\u2B1C ";
				else
					file << u8"\u2B1B ";
			}
			else
			{
				if ((i + j + 1) % 2 == 0)
					file << u8"\u2B1C";
				else
					file << u8"\u2B1B";
			}
		}
		file << "|" << i + 1 << std::endl;
		if (i == 7)
			break ;
	}
	file << " +---------------------------+\n";
	file << "   A  B   C  D   E  F   G  H\n";
}