class MapMaker
{
  public:

	enum Selection
	{
		all,
		top,
		right,
		left,
		bottom

	}

    
    MapMaker();
    ~MapMaker();
  
  	void run();

  private:

  	void fillAll();
  	void fillBorder(Selection borderChoice);
    void createMap();
};
