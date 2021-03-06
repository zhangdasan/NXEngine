#include "TCSphere.h"

static unsigned int State;

TCSphere::TCSphere():camera(NX::float3(0, 0, -500), NX::float3(0, 0, 1), NX::float3(0, 1, 0), 90, 1, 1, 3000){
}

TCSphere::~TCSphere(){
}

bool TCSphere::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//vertex data
        v[0] = {NX::float4(0, 0, 0, 10)};
    }
    
    {//vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    }
    
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, vPosition));
        glEnableVertexAttribArray(0);
    }
    
    {//ibo
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./redBook/Chap9/TSSphereVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redBook/Chap9/TSSphereFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->AddShader("./redbook/Chap9/TSSphereTCS.glsl", GL_TESS_CONTROL_SHADER);
        m_pg->AddShader("./redbook/chap9/TSSphereTES.glsl", GL_TESS_EVALUATION_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        MVPLocation  = glGetUniformLocation(m_pg->GetId(), "MVP");
        OutLocation  = glGetUniformLocation(m_pg->GetId(), "Outer");
        OutValue     = 5;
    }
    
    return true;
}

void TCSphere::Tick(const double DeltaTime){
    Application::Tick(DeltaTime);
}

void TCSphere::Render(){
    glClearColor(0.3, 0.3, 0.3, 0);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glPatchParameteri(GL_PATCH_VERTICES, 1);
    auto MVP = camera.GetWatchMatrix();
    glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    glUniform1i(OutLocation, OutValue);
    glDrawArrays(GL_PATCHES, 0, 1);
}

void TCSphere::OnCursorPositionEvent(double xByScreen, double yByScreen){
    static double xPrePos = xByScreen;
    static double yPrePos = yByScreen;
    if(State == 1){
        camera.RotateByUpDownAxis((xByScreen - xPrePos) * 0.001);
        camera.RotateByLeftRightAxis((yByScreen - yPrePos) * 0.001);
    }else if(State == 2){
    }
    xPrePos = xByScreen;
    yPrePos = yByScreen;
}

void TCSphere::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    if(action != GLFW_PRESS){
        State = 0;
        return;
    }
    if(key == GLFW_KEY_LEFT_CONTROL){
        State = 1;
    }else if(key == GLFW_KEY_LEFT_ALT){
        State = 2;
    }
    if(key == GLFW_KEY_LEFT){
        camera.MoveLeft(50);
    }else if(key == GLFW_KEY_RIGHT){
        camera.MoveRight(50);
    }else if(key == GLFW_KEY_UP){
        camera.MoveUp(50);
    }else if(key == GLFW_KEY_DOWN){
        camera.MoveDown(50);
    }else if(key == GLFW_KEY_W){
        camera.MoveFront(50);
    }else if(key == GLFW_KEY_S){
        camera.MoveBack(50);
    }else if(key == GLFW_KEY_PAGE_UP){
        camera.RotateByLeftRightAxis(NX::DG2RD(15));
    }else if(key == GLFW_KEY_PAGE_DOWN){
        camera.RotateByLeftRightAxis(-NX::DG2RD(15));
    }else if(key == GLFW_KEY_1){
        OutValue += 2;
    }else if(key == GLFW_KEY_2){
        OutValue -= 2;
        NX::ClampFloor(OutValue, 1);
    }
}
