
/*由于使用了glfw，在glfw中只支持UTF-8编码的文字，所以必须在项目中设置使用Unicode字符集*/
bool gsgInit(const char*);

//模型类
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