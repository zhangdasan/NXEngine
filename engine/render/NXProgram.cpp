#include "NXProgram.h"
#include "NXLog.h"
#include "NXShaderManager.h"

NX::Program::Program(){
    m_vShaderSet.clear();
    m_uProgramId = glCreateProgram();
}

NX::Program::~Program(){
    if(m_uProgramId != 0){
        glDeleteProgram(m_uProgramId);
        m_uProgramId = 0;
    }
}

void NX::Program::AddShader(NX::Shader *shader){
    m_vShaderSet.push_back(shader);
}

void NX::Program::AddShader(const std::string &strShaderFilePath, GLenum ShaderType){
    AddShader(ShaderManager::Instance().FetchShader(strShaderFilePath, ShaderType));
}

std::string NX::Program::LinkProgram(){
    for(int i = 0, len = (int)m_vShaderSet.size(); i < len; ++i){
        if(m_vShaderSet[i] == NULL){
            continue;
        }
        glAttachShader(m_uProgramId, (int)(*m_vShaderSet[i]));
    }
    glLinkProgram(m_uProgramId);
    std::string strErr(256,0);
    glGetProgramInfoLog(m_uProgramId, int(strErr.size()-1), NULL, &(strErr[0]));
    glb_GetLog().log("Link program with link msg [%s]",(strErr[0] == 0 ? "link succeed" : strErr.c_str()));
    return strErr;
}

void NX::Program::UseProgram(){
    glUseProgram(m_uProgramId);
}

