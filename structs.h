struct Rule
{
	int beginRm;
	char direction;
	int destRm;
};
struct Effect
{
    int effectID;
    int effectAmt;
    string attribute;
};
struct RollEffect
{
	string dice;
	string Hatt;
	int hRoll;
	int hEffect;
	int hrAmt;
	string hMess;
	string Matt;
	int mRoll;
	int mEffect;
	int mrAmt;
	string mMess;
	string Latt;
	int lRoll;
	int lEffect;
	int lrAmt;
	string lMess;
};
struct InstaEffect
{
	int dmgAmt;
	int dmgTypeRm;
	string dmgAtt;
};
