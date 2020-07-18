#pragma once 
struct TextInfo
{
	Vec2 Position;
	std::string Str;
};
class TextUIMgr : public Singleton<TextUIMgr>
{
public:
	TextUIMgr();
	~TextUIMgr();

	int m_NextKey;

	std::map<int,TextMgr*> m_Texts;
	std::vector<TextInfo*> m_TextInfos;

	void Init();
	void Release();

	void AddText(int height,bool bold,bool itailc,const std::string str ,Vec2 pos = Vec2(0,0));
	void InitText(int key, int height, bool bold, bool itailc, const std::string str);
	void InitText(int key,Vec2 Pos);
	void InitText(int key, std::string str);

	void Update();
	void Render();
};

