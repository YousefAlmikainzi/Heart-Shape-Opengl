#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define RESOLUTION_Y 800
#define RESOLUTION_X 1000

float obj_Vertices[] =
{
    //back -Z
    -.5f, -.5f, -.5,//0
    .5f, -.5f, -.5,//1
    -.5f, .5f, -.5,//2
    .5f, .5f, -.5,//3

    //front +Z
    -.5f, -.5f, .5,//4
    .5f, -.5f, .5,//5
    -.5f, .5f, .5,//6
    .5f, .5f, .5,//7

    //left -X
    -.5f, -.5f, -.5,//8
    -.5f, -.5f, .5,//9
    -.5f, .5f, -.5,//10
    -.5f, .5f, .5,//11

    //right +X
    .5f, -.5f, -.5,//12
    .5f, -.5f, .5,//13
    .5f, .5f, -.5,//14
    .5f, .5f, .5,//15

    //down -Y
    -.5f, -.5f, -.5,//16
    .5f, -.5f, -.5,//17
    -.5f, -.5f, .5,//18
    .5f, -.5f, .5,//19

    //up +Y
    -.5f, .5f, -.5,//20
    .5f, .5f, -.5,//21
    -.5f, .5f, .5,//22
    .5f, .5f, .5//23
};

unsigned int indices[] = {
    0, 1, 3,
    3, 2, 0,

    4, 5, 7,
    7, 6, 4,

    8, 9, 11,
    11, 10, 8,

    12, 13, 15,
    15, 14, 12,

    16, 17, 19,
    19, 18, 16,

    20, 21, 23,
    23, 22, 20
};

float normals[] = {
    //back -Z
    0.0f,0.0f,-1.0f,
    0.0f,0.0f,-1.0f,
    0.0f,0.0f,-1.0f,
    0.0f,0.0f,-1.0f,

    //front +Z
    0.0f,0.0f,1.0f,
    0.0f,0.0f,1.0f,
    0.0f,0.0f,1.0f,
    0.0f,0.0f,1.0f,

    //left -X
    -1.0f,0.0f,0.0f,
    -1.0f,0.0f,0.0f,
    -1.0f,0.0f,0.0f,
    -1.0f,0.0f,0.0f,

    //right +X
    1.0f,0.0f,0.0f,
    1.0f,0.0f,0.0f,
    1.0f,0.0f,0.0f,
    1.0f,0.0f,0.0f,

    //down -Y
    0.0f,-1.0f,0.0f,
    0.0f,-1.0f,0.0f,
    0.0f,-1.0f,0.0f,
    0.0f,-1.0f,0.0f,

    //up +Y
    0.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f
};

float uv[]=
{
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};

float colors[] = {
    0.82f, 0.14f, 0.67f,
    0.31f, 0.95f, 0.22f,
    0.76f, 0.48f, 0.09f,
    0.13f, 0.61f, 0.88f,

    0.54f, 0.27f, 0.73f,
    0.91f, 0.39f, 0.15f,
    0.08f, 0.84f, 0.56f,
    0.47f, 0.18f, 0.99f,

    0.65f, 0.72f, 0.11f,
    0.24f, 0.43f, 0.81f,
    0.97f, 0.58f, 0.36f,
    0.19f, 0.06f, 0.92f,

    0.74f, 0.33f, 0.50f,
    0.40f, 0.89f, 0.28f,
    0.57f, 0.12f, 0.79f,
    0.03f, 0.68f, 0.45f,

    0.86f, 0.25f, 0.60f,
    0.29f, 0.77f, 0.16f,
    0.51f, 0.34f, 0.94f,
    0.98f, 0.55f, 0.07f,

    0.17f, 0.83f, 0.41f,
    0.63f, 0.20f, 0.70f,
    0.36f, 0.97f, 0.53f,
    0.11f, 0.49f, 0.85f
};

typedef struct
{
    float x, y, z;
} Vec3;

typedef struct
{
    float m[16];
} mat4;


void framebuffer(GLFWwindow* window, int width, int height);
void readEntireFile(char* strBuffer, FILE* shaderFile);
mat4 M_Identity();
mat4 M_Translate(float x, float y, float z);
mat4 M_Scale(float sx, float sy, float sz);
mat4 M_MulMatrix(mat4 a, mat4 b);
mat4 M_Rotate_Z(float angle);
mat4 M_Rotate_X(float angle);
mat4 M_Rotate_Y(float angle);
mat4 M_Perspective(float fovyRadians, float aspect, float nearZ, float farZ);
mat4 M_LookAt(Vec3 position, Vec3 target, Vec3 worldUp);

int main()
{
    FILE *vertexHLSL = fopen("VertexShader1.vs", "r");
    FILE *fragmentHLSL = fopen("StepMixSmooth.fs", "r");
    char *vertexString = malloc(sizeof(char) * 20000);
    char *fragmentString = malloc(sizeof(char) * 20000);

    readEntireFile(vertexString, vertexHLSL);
    const char* vertexSource = vertexString;
    fclose(vertexHLSL);

    readEntireFile(fragmentString, fragmentHLSL);
    const char* fragmentSource = fragmentString;
    fclose(fragmentHLSL);

    glfwInit();
    GLFWwindow *window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "OpenGlScene", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((void*)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetFramebufferSizeCallback(window, framebuffer);

    //vertex shader
    unsigned int vertexShaderID = 0;
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(vertexShaderID);

    //fragment shader
    unsigned int fragmentShaderID = 0;
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShaderID);

    unsigned int shaderProgram = 0;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderID);
    glAttachShader(shaderProgram, fragmentShaderID);
    glLinkProgram(shaderProgram);

    free(vertexString);
    free(fragmentString);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    unsigned int VAO, VBO, NRS, EBO, CLR, UV;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(obj_Vertices), obj_Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //ebo
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);

    //bind normals
    glGenBuffers(1, &NRS);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, NRS);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //bind colors
    glGenBuffers(1, &CLR);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, CLR);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //bind uv
    glGenBuffers(1, &UV);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, UV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projLoc = glGetUniformLocation(shaderProgram, "projection");

    int colorLoc = glGetUniformLocation(shaderProgram, "uColor");


    Vec3 cameraPos = {0.0f, 0.0f, 5.0f};
    Vec3 cameraTarget = {0.0f, 0.0f, 0.0f};
    Vec3 worldUp = {0.0f, 1.0f, 0.0f};

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.1f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        //float angleTime = glfwGetTime();

        mat4 cube = M_Translate(0.0f, 0.0f, 0.0f);
        cube = M_MulMatrix(cube, M_Rotate_X(0.0f));
        cube = M_MulMatrix(cube, M_Rotate_Y(0.0f));
        cube = M_MulMatrix(cube, M_Rotate_Z(15.7f));
        cube = M_MulMatrix(cube, M_Scale(1.0f, 1.0f, 1.0f));

        mat4 view = M_LookAt(cameraPos, cameraTarget, worldUp);
        view = M_MulMatrix(view, M_Rotate_Y(0.0f));

        float fov = 45.0f * (3.14159265f / 180.0f);
        float aspect = (float)RESOLUTION_X/RESOLUTION_Y;
        mat4 projection = M_Perspective(fov, aspect, 0.1f, 100.0f);

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view.m[0]);

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection.m[0]);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &cube.m[0]);

        glBindVertexArray(VAO);

        glUniform3f(colorLoc, 0.0f, 1.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    return 0;
}

void framebuffer(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width, height);
}

void readEntireFile(char* strBuffer, FILE* shaderFile)
{
    fseek(shaderFile, 0, SEEK_END);
    long fileSize = ftell(shaderFile);
    rewind(shaderFile);
    fread(strBuffer, 1, fileSize, shaderFile);
    strBuffer[fileSize] = '\0';
}

mat4 M_Identity()
{
    mat4 I = {0};

    I.m[0] = 1;
    I.m[5] = 1;
    I.m[10] = 1;
    I.m[15] = 1;
    return I;
}

mat4 M_Translate(float x, float y, float z)
{
    mat4 T = M_Identity();
    T.m[12] = x;
    T.m[13] = y;
    T.m[14] = z;
    return T;
}

mat4 M_Scale(float sx, float sy, float sz)
{
    mat4 S = M_Identity();

    S.m[0] = sx;
    S.m[5] = sy;
    S.m[10] = sz;

    return S;
}
mat4 M_Rotate_Z(float angle)
{
    mat4 R = M_Identity();
    float c = cos(angle);
    float s = sin(angle);

    R.m[0] = c;
    R.m[1] = s;
    R.m[4] = -s;
    R.m[5] = c;

    return R;
}

mat4 M_Rotate_X(float angle)
{
    mat4 R = M_Identity();
    float c = cos(angle);
    float s = sin(angle);

    R.m[5] = c;
    R.m[6] = s;
    R.m[9] = -s;
    R.m[10] = c;

    return R;
}

mat4 M_Rotate_Y(float angle)
{
    mat4 R = M_Identity();
    float c = cos(angle);
    float s = sin(angle);

    R.m[0] = c;
    R.m[2] = -s;
    R.m[8] = s;
    R.m[10] = c;

    return R;
}

mat4 M_MulMatrix(mat4 a, mat4 b)
{
    mat4 result = {0};
    int matrixSize = 4;

    for(int col = 0; col < matrixSize; col++)
    {
        for(int row = 0; row < matrixSize; row++)
        {
            float sum = 0.0f;
            for(int i = 0; i <matrixSize; i++)
            {
                sum += a.m[i*4 + row] * b.m[col*4 + i];
            }
            result.m[col * 4 + row] = sum;
        }
    }
    return result;
}

mat4 M_Perspective(float fovyRadians, float aspect, float nearZ, float farZ)
{
    float f = 1.0f / tanf(fovyRadians * 0.5f);
    mat4 P = {0};

    P.m[0]  = f / aspect;
    P.m[5]  = f;
    P.m[10] = (farZ + nearZ) / (nearZ - farZ);
    P.m[11] = -1.0f;
    P.m[14] = (2.0f * farZ * nearZ) / (nearZ - farZ);

    return P;
}

Vec3 get_crossProduct(Vec3 A, Vec3 B)
{
    Vec3 r;

    r.x = (A.y * B.z) - (A.z * B.y);
    r.y = (A.z * B.x) - (A.x * B.z);
    r.z = (A.x * B.y) - (A.y * B.x);

    return r;
}

mat4 M_LookAt(Vec3 position, Vec3 target, Vec3 worldUp)
{
    mat4 c = M_Identity();

    //forward
    Vec3 forward;
    forward.x = position.x - target.x;
    forward.y = position.y - target.y;
    forward.z = position.z - target.z;
    float forwardRoot = sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
    forward.x = forward.x /forwardRoot;
    forward.y = forward.y /forwardRoot;
    forward.z = forward.z /forwardRoot;

    c.m[2] = forward.x;
    c.m[6] = forward.y;
    c.m[10] = forward.z;

    //right
    Vec3 defualtUp = {0, 1, 0};
    Vec3 right = get_crossProduct(forward, defualtUp);
    float rightRoot = sqrt(right.x * right.x + right.y * right.y + right.z * right.z);

    right.x = right.x / rightRoot;
    right.y = right.y / rightRoot;
    right.z = right.z / rightRoot;

    c.m[0] = right.x;
    c.m[4] = right.y;
    c.m[8] = right.z;

    //up
    Vec3 up = get_crossProduct(forward, right);
    float upRoot = sqrt(up.x * up.x + up.y * up.y + up.z * up.z);
    up.x = up.x /upRoot;
    up.y = up.y /upRoot;
    up.z = up.z /upRoot;

    c.m[1] = up.x;
    c.m[5] = up.y;
    c.m[9] = up.z;

    mat4 translation = M_Translate(-position.x, -position.y, -position.z);
    return M_MulMatrix(c, translation);
}
