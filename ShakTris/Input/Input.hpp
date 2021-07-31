#pragma once



namespace Shakkar {

    class inputBitmap
    {
    public:
        bool left       : 1;
        bool right      : 1;
        bool rotRight   : 1;
        bool rotLeft    : 1;
        bool rot180     : 1;
        bool hold       : 1;
        bool hardDrop   : 1;
        bool softDrop   : 1;
        bool menuUp     : 1;
        bool menuDown   : 1;
        bool menuLeft   : 1;
        bool menuRight  : 1;
        bool menuSelect : 1;

        inputBitmap();

        void setLeft();
        void setRight();
        void setRotRight();
        void setRotLeft();
        void setRot180();
        void setHold();
        void setHardDrop();
        void setSoftDrop();
        void setMenuUp();
        void setMenuDown();
        void setMenuLeft();
        void setMenuRight();
        void setMenuSelect();

        void unsetLeft();
        void unsetRight();
        void unsetRotRight();
        void unsetRotLeft();
        void unsetRot180();
        void unsetHold();
        void unsetHardDrop();
        void unsetSoftDrop();
        void unsetMenuUp();
        void unsetMenuDown();
        void unsetMenuLeft();
        void unsetMenuRight();
        void unsetMenuSelect();

    private:
    };
    extern inputBitmap input;
};