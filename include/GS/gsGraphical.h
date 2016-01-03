
/*����ʹ����glfw����glfw��ֻ֧��UTF-8��������֣����Ա�������Ŀ������ʹ��Unicode�ַ���*/
bool gsgInit(const char*);

//ģ����
class model
{
public:
	struct pointData
	{
		float VerticesData;
		float NormalsData;
		float TextureData;

		pointData(float VerticesData, float NormalsData, float TextureData);
	};

	bool loadModel(const char*);

	void clear();

	void addPoint(float VerticesPos, float NormalsPos, float TeturePos);

	unsigned int size();

	pointData operator [](int i);
};