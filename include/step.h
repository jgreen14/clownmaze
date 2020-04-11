#ifndef STEP_H
#define STEP_H

class Step
{
    public:
        Step();
        Step(float, float);
        virtual ~Step();
        float getX();
        float getY();
        float getLength2();
        float getOffset();
        float getHeight();
        float getDistance();
        float getShading();
        void copy(Step*);
        void setX(float);
        void setY(float);
        void setLength2(float);
        void setOffset(float);
        void setHeight(float);
        void setDistance(float);
        void setShading(float);
    protected:
    private:
        float x;
        float y;
        float length2;
        float offset;
        float height;
        float distance;
        float shading;
};

#endif // STEP_H
