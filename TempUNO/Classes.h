#include "Header.h"


class cCard {
protected:
	short Value;
	short CardColor;
	bool Special;
	bool Visible = false;
	Point Position;


public:
	bool Hovered = false;

	cCard(short _color) {
		this->CardColor = _color;
		this->Special = true;
	}
	cCard(short _color, short _value) {
		this->CardColor = _color;
		this->Value = _value;
		this->Special = false;
	}

	void setPoint(Point Center, bool Horizontal, short handSize, short cardIndex) {
		Position = Point(Center.X + (Spacing * handSize / 2 - cardWidth * handSize / 2 + (cardWidth - Spacing) *cardIndex)*Horizontal - cardWidth / 2 * (!Horizontal),
			Center.Y + (+Spacing * handSize / 2 - cardHeight * handSize / 2 + (cardHeight - Spacing) *cardIndex)*(!Horizontal) - cardHeight / 2 * Horizontal - 5 * (Hovered));
	}
	short getValue() {
		return this->Value;
	}
	short getColor() {
		return this->CardColor;
	}
	bool getSpecial() {
		return this->Special;
	}
	bool getVisible() {
		return this->Visible;
	}
	void makeVisible() {
		this->Visible = true;
	}
	void makeInvisible() {
		this->Visible = false;
	}
	virtual Rectangle getCardArea() abstract;
	Rectangle getPosition() {
		return Rectangle(this->Position.X, this->Position.Y, cardWidth, cardHeight);
	}
};

class cPlayer {
	Point Center;
	bool Horizontal; //0 Vertical - 1 Horizontal
	Point setPosition(short playerCount, short playerIndex) {
		if (playerIndex == 0) {
			this->Horizontal = true;
			return Point(640, 680 - cardHeight + cardHeight / 2);
		}
		if (playerIndex == 1) {
			this->Horizontal = false;
			return Point(1240 - cardWidth + cardWidth / 2, 360);
		}
		switch (playerCount) {
		case 3:
			this->Horizontal = false; return Point(40 + cardWidth / 2, 360);
		case 4:
			switch (playerIndex) {
			case 2: this->Horizontal = true; return Point(640, 40 + cardHeight / 2);
			case 3: this->Horizontal = false;  return Point(40 + cardWidth / 2, 360);
			}
		case 5:
			switch (playerIndex) {
			case 2: this->Horizontal = true; return Point(960 - cardWidth, 40 + cardHeight / 2);
			case 3: this->Horizontal = true; return Point(320 + cardWidth, 40 + cardHeight / 2);
			case 4: this->Horizontal = false;  return Point(40 + cardWidth / 2, 360);
			}
		}
	}
public:
	vector <cCard*>* Hand;
	vector <short> score;

	cPlayer(short playerCount, short playerIndex) {
		Hand = new vector <cCard*>;
		this->Center = this->setPosition(playerCount, playerIndex);
	}
	~cPlayer() {
		delete this->Hand;
	}

	void addScore(short _score) {
		this->score.push_back(_score);
	}
	String^ getName(short playerIndex) {
		switch (playerIndex) {
		case 0:	return "You";
		case 1:	return "Elvia";
		case 2:	return "Diego";
		case 3: return "Maria";
		case 4:	return "Bryam";
		}
	}
	Point getCenter() {
		return this->Center;
	}
	bool getHorizontal() {
		return this->Horizontal;
	}
};


class cNormalCard : public cCard {
	short Number;
public:
	cNormalCard(short _color, short _number) : cCard(_color, _number) {
		this->Number = _number;
		this->Value = _number;
	}
	short getNumber() {
		return this->Number;
	}
	Rectangle getCardArea() {
		if (this->getVisible()) {
			if (this->Number) return Rectangle(CardBmpDim / 10 * (this->Number - 1), CardBmpDim / 7 * (this->getColor()),
				CardBmpDim / 10, CardBmpDim / 7);
			else return Rectangle(CardBmpDim / 10 * (this->getColor()), 0,
				CardBmpDim / 10, CardBmpDim / 7);
		}
		else return Rectangle(0, 0, cardWidth, cardHeight);
	}
};

class cEffectCard : public cCard {
	short Effect;
	void assignValue() {
		if (this->Effect == Skip || this->Effect == Reverse || this->Effect == DrawTwo) this->Value = 20;
		else this->Value = 50;
	}
public:
	cEffectCard(short _color, short _effect) : cCard(_color) {
		this->Effect = _effect;
		this->assignValue();
	}
	short getEffect() {
		return this->Effect;
	}
	Rectangle getCardArea() {
		if (this->Effect >= Wild)
			return Rectangle(CardBmpDim / 10 * 9, CardBmpDim / 7 * ((this->Effect != Wild) * 2),
				CardBmpDim / 10, CardBmpDim / 7);
		else return Rectangle(CardBmpDim / 10 * (this->Effect == Reverse ? (this->getColor() <= Yellow ? 8 + (this->getColor() == Yellow) : 0 + (this->getColor() == Green)) : (this->getColor() + 4 * (this->Effect == DrawTwo)))
			, CardBmpDim / 7 * (4 + (this->Effect == Reverse && this->getColor() >= Blue))
			, CardBmpDim / 10, CardBmpDim / 7);
	}
};


public ref class cPrintCards {
	BufferedGraphics ^Buffer;
	Bitmap ^bmpCardFront, ^bmpCardZero, ^bmpCardBack, ^tempBMP;
	void setBMP(cCard *Card) {
		if (Card->getVisible())
			if (Card->getValue())
				this->tempBMP = this->bmpCardFront;
			else this->tempBMP = this->bmpCardZero;
		else this->tempBMP = this->bmpCardBack;
	}
public:
	cPrintCards(BufferedGraphics ^_buffer) {
		this->Buffer = _buffer;
		this->bmpCardFront = gcnew Bitmap("Assets//CardFront.png");
		this->bmpCardZero = gcnew Bitmap("Assets//CardZero.png");
		this->bmpCardBack = gcnew Bitmap("Assets//CardBack.png");
	}
	~cPrintCards() {
		delete this->bmpCardFront;
		delete this->bmpCardZero;
		delete this->bmpCardBack;
	}
	void printCard(cCard *Card) {
		setBMP(Card);
		if (Card->getVisible()) {
			Buffer->Graphics->DrawImage(tempBMP, Card->getPosition(), Card->getCardArea(), GraphicsUnit::Pixel);
		}
		else	Buffer->Graphics->DrawImage(tempBMP, Card->getPosition());
	}
	void printStack(cCard *Card) {
		setBMP(Card);
		Buffer->Graphics->DrawImage(tempBMP, Rectangle(clientWidth / 2 - cardWidth / 2, clientHeight / 2 - cardHeight / 2, cardWidth, cardHeight), Card->getCardArea(), GraphicsUnit::Pixel);
	}
	void printDeck(Rectangle _deckPosition) {
		Buffer->Graphics->DrawImage(bmpCardBack, _deckPosition);
	}
};


class cMatch {

	short currentPlayer;
	short Direction = 1;

	bool Player2Stack(short cardIndex) {
		this->Stack->push_back(this->Players->at(currentPlayer)->Hand->at(cardIndex));
		this->Players->at(currentPlayer)->Hand->erase(this->Players->at(currentPlayer)->Hand->begin() + cardIndex);
		this->Stack->back()->makeVisible();
		if (!this->Players->at(currentPlayer)->Hand->size())
			return true;

		if (this->Stack->back()->getSpecial())
			switch (((cEffectCard*)this->Stack->back())->getEffect()) {
			case Skip:
				this->nextTurn();
				this->nextTurn();
				break;

			case Reverse:
				this->changeDirection();
				this->nextTurn();
				break;

			case DrawTwo:
				this->nextTurn();
				this->drawCard();
				this->drawCard();
				this->nextTurn();
				break;

			case Wild:
				this->needColorPick = true;
				break;

			case WildDrawFour:
				this->needColorPick = true;
				break;
			}
		else this->nextTurn();
		return false;
	}

	void refillDeck() {
		for (short t = this->Stack->size() - 2; t >= 0; t--) {
			this->Deck->push_back(this->Stack->at(t));
			this->Deck->back()->makeInvisible();
			this->Stack->erase(this->Stack->begin() + t);
		}
		this->shuffle();
	}
	
	short tempColor;
public:
	short cheatQT = 3;
	bool usingTempColor = false;
	vector <cPlayer*> *Players;
	vector <cCard*> *Deck, *Stack;
	bool deckHovered;
	bool tryCheat = false;
	bool needColorPick = false;

	String^ getWinner() {
		switch (currentPlayer) {
		case 0: return "You Won";
		case 1: return "Elvia Won";
		case 2: return "Diego Won";
		case 3: return "Maria Won";
		case 4: return "Bryam Won";
		}
	}

	bool verifyPlay(cCard *_card) {
		if (this->Stack->size()) {
			if (_card->getColor() == Black) return true;
			if (this->usingTempColor)
				if (_card->getColor() == this->tempColor) return true;
			if (_card->getColor() == this->Stack->back()->getColor()) return true;
			if (_card->getSpecial() && this->Stack->back()->getSpecial()) {
				if (((cEffectCard*)_card)->getEffect() == ((cEffectCard*)this->Stack->back())->getEffect())
					return true;
			}
			else if (!_card->getSpecial() && !this->Stack->back()->getSpecial())
				if (_card->getValue() == this->Stack->back()->getValue())
					return true;
			return false;
		}
		else return true;
	}

	cMatch(vector <cCard*> *_deck, vector<cPlayer*> *_players, vector <cCard*> *_stack) {
		this->Players = _players;
		this->Deck = _deck;
		this->Stack = _stack;
		this->shuffle();
		short Dealer = pickDealer();
		for (short i = 0; i<7; i++)
			for (short i1 = 0; i1 < Players->size(); i1++) {
				currentPlayer = i1 + Dealer;
				if (currentPlayer >= Players->size()) currentPlayer -= Players->size();
				Players->at(currentPlayer)->Hand->push_back(Deck->back());
				Deck->pop_back();
			}
		for (short c = 0; c < this->Players->at(0)->Hand->size(); c++)
			this->Players->at(0)->Hand->at(c)->makeVisible();
		this->Stack->push_back(this->Deck->back());
		this->Stack->back()->makeVisible();
		this->Deck->pop_back();
		this->currentPlayer = Dealer;
	}
	~cMatch() {
		short tempScore = 0;
		for (short i = 0; i < this->Players->size(); i++)
			for (short c = this->Players->at(i)->Hand->size() - 1; c >= 0; c--) {
				tempScore += this->Players->at(i)->Hand->back()->getValue();
				this->Deck->push_back(this->Players->at(i)->Hand->back());
				this->Deck->back()->makeInvisible();
				this->Players->at(i)->Hand->pop_back();
			}
		for (short i = 0; i < this->Players->size(); i++) {
			if (i == this->currentPlayer)
				this->Players->at(currentPlayer)->addScore(tempScore);
			else this->Players->at(i)->addScore(0);
		}
		for (short i = this->Stack->size() - 1; i >= 0; i--) {
			this->Deck->push_back(this->Stack->back());
			this->Deck->back()->makeInvisible();
			this->Stack->pop_back();
		}
	}

	short cheat(Point mousePosition) {
		for (short playerIndex = 1; playerIndex < this->Players->size(); playerIndex++)
			for (short cardIndex = this->Players->at(playerIndex)->Hand->size() - 1; cardIndex >= 0; cardIndex--)
				if (this->Players->at(playerIndex)->Hand->at(cardIndex)->getPosition().Contains(mousePosition)) {
					this->Players->at(playerIndex)->Hand->at(cardIndex)->makeVisible();
					this->cheatQT--;
					return cheatQT;
				}
		return cheatQT;
	}

	void drawCard() {
		this->Players->at(currentPlayer)->Hand->push_back(this->Deck->back());
		if (!currentPlayer)
			this->Players->at(currentPlayer)->Hand->back()->makeVisible();
		this->Deck->pop_back();
		if (!this->Deck->size())
			refillDeck();
	}

	bool playCard(short cardIndex) {
		if (verifyPlay(this->Players->at(currentPlayer)->Hand->at(cardIndex))) {
			if (this->Player2Stack(cardIndex))
				return true;
			return false;
		}
	}

	void changeDirection() {
		this->Direction *= -1;
	}
	void nextTurn() {
		this->currentPlayer += this->Direction;
		if (this->currentPlayer < 0) currentPlayer = this->Players->size() - 1;
		else if (this->currentPlayer > this->Players->size() - 1) this->currentPlayer = 0;
	}

	void setTempColor(short _color) {
		this->tempColor = _color;
		this->needColorPick = false;
		this->usingTempColor = true;
		this->nextTurn();
		if (((cEffectCard*)this->Stack->back())->getEffect() == WildDrawFour) {
			this->drawCard();
			this->drawCard();
			this->drawCard();
			this->drawCard();
			this->nextTurn();
		}
	}
	String^ getTempColor() {
		switch (this->tempColor) {
		case Red:	 return "Red";
		case Yellow: return "Yellow";
		case Blue:	 return "Blue";
		case Green:	 return "Green";
		}
	}
	short getCurrentPlayer() {
		return this->currentPlayer;
	}
	short getDirection() {
		return this->Direction;
	}

	short pickDealer() {
		vector <short> tempCardVector;
		short highestCard, highestPlayer;

		for (short t = 0; t < this->Players->size(); t++) {
			while (this->Deck->back()->getValue() > 9) {
				this->Stack->push_back(this->Deck->back());
				this->Deck->pop_back();
			}
			tempCardVector.push_back(this->Deck->back()->getValue());
			this->Stack->push_back(this->Deck->back());
			this->Deck->pop_back();
			if (tempCardVector.at(t) > highestCard) {
				highestPlayer = t;
				highestCard = tempCardVector.at(t);
			}
		}
		return highestPlayer;
	}
	void shuffle() {
		unsigned seed = time(NULL);
		std::shuffle(this->Deck->begin(), this->Deck->end(), std::default_random_engine(seed));
	}
	Rectangle getDeckPosition() {
		return Rectangle(400, 220 - 5 * deckHovered, cardWidth, cardHeight);
	}
};

class cGame {
public:
	vector <cPlayer*> *Players;
	vector <cCard*> *Deck, *Stack;
	cMatch *Match = NULL;
	cGame() {
		this->Players = new vector<cPlayer*>;
		this->Deck = new vector<cCard*>;
		this->Stack = new vector<cCard*>;
		for (short c = 0; c < 4; c++) {
			this->Deck->push_back(new cNormalCard(c, 0));
			for (short n = 1; n < 10; n++) {
				this->Deck->push_back(new cNormalCard(c, n));
				this->Deck->push_back(new cNormalCard(c, n));
			}
			for (short e = 0; e < 3; e++) {
				this->Deck->push_back(new cEffectCard(c, e));
				this->Deck->push_back(new cEffectCard(c, e));
			}
		}
		for (short t = 0; t < 4; t++) {
			this->Deck->push_back(new cEffectCard(4, 3));
			this->Deck->push_back(new cEffectCard(4, 4));
		}
		//Feel free to change to 3-5 Players //Will be a function
	}
	void addPlayers(short playerCount) {
		for (short playerIndex = 0; playerIndex < playerCount; playerIndex++) {
			this->Players->push_back(new cPlayer(playerCount, playerIndex));
		}
	}
	void removePlayers() {
		for (short i = this->Players->size() - 1; i >= 0; i--) {
			delete this->Players->at(i);
			this->Players->pop_back();
		}
	}
	//void addPlayer() {
	//	this->Players->push_back(new cPlayer(2,2));
	//}
	~cGame() {
		for (short i = 0; i < this->Players->size(); i++)
			delete Players->at(i);
		for (short i = 0; i < this->Deck->size(); i++)
			delete Deck->at(i);
		for (short i = 0; i < this->Stack->size(); i++)
			delete Stack->at(i);
		delete this->Players;
		delete this->Deck;
		delete this->Stack;
	}
	void startMatch() {
		this->Match = new cMatch(this->Deck, this->Players, this->Stack);
	}
	void endMatch() {
		if (this->Match) {
			delete Match;
			this->Match = NULL;
		}
	}
};