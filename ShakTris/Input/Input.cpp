
#include "Input.hpp"
namespace Shakkar {
    inputBitmap::inputBitmap() : left(0), right(0), rotRight(0), rotLeft(0), rot180(0), hold(0), hardDrop(0), softDrop(0), 
		menuUp(0), menuDown(0), menuLeft(0), menuRight(0), menuSelect(0) {}
	
	void inputBitmap::setLeft()		{ left = true;		}
	void inputBitmap::setRight()	{ right = true;		}
	void inputBitmap::setRotRight() { rotRight = true;	}
	void inputBitmap::setRotLeft()	{ rotLeft = true;	}
	void inputBitmap::setRot180()	{ rot180 = true;	}
	void inputBitmap::setHold()		{ hold = true;		}
	void inputBitmap::setHardDrop() { hardDrop = true;	}
	void inputBitmap::setSoftDrop() { softDrop = true;	}
	void inputBitmap::setMenuUp()		{ menuUp = true;	}
	void inputBitmap::setMenuDown()		{ menuDown = true;	}
	void inputBitmap::setMenuLeft()		{ menuLeft = true;	}
	void inputBitmap::setMenuRight()	{ menuRight = true; }
	void inputBitmap::setMenuSelect()	{ menuSelect = true;}

	void inputBitmap::unsetLeft()		{ left = false;		}
	void inputBitmap::unsetRight()		{ right = false;	}
	void inputBitmap::unsetRotRight()	{ rotRight = false; }
	void inputBitmap::unsetRotLeft()	{ rotLeft = false;	}
	void inputBitmap::unsetRot180()		{ rot180 = false;	}
	void inputBitmap::unsetHold()		{ hold = false;		}
	void inputBitmap::unsetHardDrop()	{ hardDrop = false; }
	void inputBitmap::unsetSoftDrop()	{ softDrop = false; }
	void inputBitmap::unsetMenuUp()		{ menuUp = false;	 } 
	void inputBitmap::unsetMenuDown()	{ menuDown = false;	 } 
	void inputBitmap::unsetMenuLeft()	{ menuLeft = false;	 } 
	void inputBitmap::unsetMenuRight()	{ menuRight = false; } 
	void inputBitmap::unsetMenuSelect()	{ menuSelect = false;}



	inputBitmap input;
}