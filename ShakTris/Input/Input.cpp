
#include "Input.hpp"
namespace Shakkar {
	inputBitmap::inputBitmap() : left(false), right(false), rotRight(false), rotLeft(false), rot180(false),
		hold(false), hardDrop(false), softDrop(false), sonicDrop(false), menuUp(false), menuDown(false),
		menuLeft(false), menuRight(false), menuSelect(false), menuExit(false) {};
	
	void inputBitmap::setLeft()			{ this->left = true;		}
	void inputBitmap::setRight()		{ this->right = true;		}
	void inputBitmap::setRotRight()		{ this->rotRight = true;	}
	void inputBitmap::setRotLeft()		{ this->rotLeft = true;		}
	void inputBitmap::setRot180()		{ this->rot180 = true;		}
	void inputBitmap::setHold()			{ this->hold = true;		}
	void inputBitmap::setHardDrop()		{ this->hardDrop = true;	}
	void inputBitmap::setSoftDrop()		{ this->softDrop = true;	}
	void inputBitmap::setSonicDrop()	{ this->sonicDrop = true;	}
	void inputBitmap::setMenuUp()		{ this->menuUp = true;		}
	void inputBitmap::setMenuDown()		{ this->menuDown = true;	}
	void inputBitmap::setMenuLeft()		{ this->menuLeft = true;	}
	void inputBitmap::setMenuRight()	{ this->menuRight = true;	}
	void inputBitmap::setMenuSelect()	{ this->menuSelect = true;	}
	void inputBitmap::setMenuExit()		{ this->menuExit = true;	}

	void inputBitmap::unsetLeft()		{ this->left = false;		}
	void inputBitmap::unsetRight()		{ this->right = false;		}
	void inputBitmap::unsetRotRight()	{ this->rotRight = false;	}
	void inputBitmap::unsetRotLeft()	{ this->rotLeft = false;	}
	void inputBitmap::unsetRot180()		{ this->rot180 = false;		}
	void inputBitmap::unsetHold()		{ this->hold = false;		}
	void inputBitmap::unsetHardDrop()	{ this->hardDrop = false;	}
	void inputBitmap::unsetSoftDrop()	{ this->softDrop = false;	}
	void inputBitmap::unsetSonicDrop()	{ this->sonicDrop = false;	}
	void inputBitmap::unsetMenuUp()		{ this->menuUp = false;		} 
	void inputBitmap::unsetMenuDown()	{ this->menuDown = false;	} 
	void inputBitmap::unsetMenuLeft()	{ this->menuLeft = false;	} 
	void inputBitmap::unsetMenuRight()	{ this->menuRight = false;	} 
	void inputBitmap::unsetMenuSelect()	{ this->menuSelect = false;	}
	void inputBitmap::unsetMenuExit()	{ this->menuExit = false;	}

}
