#version 330

in vec3 o_normal;
in vec3 vColors;
in vec2 o_UV;

uniform vec3 uColor;
uniform sampler2D tex;
uniform sampler2D tex2;

out vec4 finalColor;

float myMix(float a, float b, float t)
{
    return a * (1.0 - t) + b * t;
}

vec3 myMix(vec3 a, vec3 b, float t)
{
    return a * (1.0 - t) + b * t;
}

float mySmoothstep(float edge0, float edge1, float x)
{
    float t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return t * t * (3.0 - 2.0 * t);
}

float myStep(float edge, float x)
{
    if (x < edge)
    {
        return 0.0;
    }
    else
    {
        return 1.0;
    }
}

float myMax(float a, float b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

float myMin(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

float myAbs(float x)
{
    if (x >= 0.0)
    {
        return x;
    }
    else
    {
        return -x;
    }
}

void main()
{
    float distanceX = myAbs(o_UV.x - .5);
    float distanceY = myAbs(o_UV.y - .5);

    float lobeY = (-0.5 * o_UV.x + 1.0) + mySmoothstep(0.5, 0.75, o_UV.x) * mySmoothstep(1.0, 0.75, o_UV.x) * .15;
    float lobeDist = myAbs(o_UV.y - lobeY);
    float lobe = 1.0 - mySmoothstep(0.0, 0.025, lobeDist);
    lobe *= myStep(.5, o_UV.y);
    lobe *= myStep(.5, o_UV.x);

    float lobeY2 = (0.5 * o_UV.x + 0.5) + mySmoothstep(0.0, 0.25, o_UV.x) * mySmoothstep(0.5, 0.25, o_UV.x) * .15;
    float lobeDist2 = myAbs(o_UV.y - lobeY2);
    float lobe2 = 1.0 - mySmoothstep(0.0, 0.025, lobeDist2);
    lobe2 *= myStep(.5, o_UV.y);
    lobe2 *= myStep(.5, 1 - o_UV.x);


    float halfDiagline1 = 1.0 - mySmoothstep(0,0.025, myAbs(o_UV.x - (0.5 - o_UV.y)));
    halfDiagline1 *= myStep(.5, 1 - o_UV.y);

    float halfDiagline3 = 1.0 - mySmoothstep(0,0.025, myAbs(o_UV.x - o_UV.y - .5));
    halfDiagline3 *= myStep(.5, o_UV.x);

    vec3 final = vec3(0,0,0);
    final = myMix(final, vec3(1.0, 0.4, 0.7), lobe);
    final = myMix(final, vec3(1.0, 0.4, 0.7), lobe2);
    final = myMix(final, vec3(1.0, 0.4, 0.7), halfDiagline1);
    final = myMix(final, vec3(1.0, 0.4, 0.7), halfDiagline3);

    //final = myMix(final, vec3(0,1,0), simplerExample1);

    finalColor = vec4(final, 1.0);
}
