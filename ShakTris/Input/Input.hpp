#pragma once



namespace Shakkar {

    class inputBitmap
    {
    private:
        bool left       : 1;
        bool right      : 1;
        bool rotRight   : 1;
        bool rotLeft    : 1;
        bool rot180     : 1;
        bool hold       : 1;
        bool hardDrop   : 1;
        bool softDrop   : 1;
    public:
        inputBitmap();

        void setLeft();
        void setRight();
        void setRotRight();
        void setRotLeft();
        void setRot180();
        void setHold();
        void setHardDrop();
        void setSoftDrop();
    
        void unsetLeft();
        void unsetRight();
        void unsetRotRight();
        void unsetRotLeft();
        void unsetRot180();
        void unsetHold();
        void unsetHardDrop();
        void unsetSoftDrop();

    };
    extern inputBitmap input;
};