#include <MAE/Rendering/Mesh/CModel.h>

void CModel::Destroy() {
	for (uint i = 0; i < m_vMeshs.size(); ++i) {
		m_vMeshs[i].m_VB->Release();
		m_vMeshs[i].m_IB->Release();
		m_vMeshs[i].m_VD->Release();
	}
	m_vMeshs.clear();
	m_vMaterials.clear();
}