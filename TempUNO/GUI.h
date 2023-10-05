#include "Classes.h"
namespace TempUNO {
	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	private:
		BufferedGraphics ^ Buffer;
		Bitmap ^bmpLogo, ^bmpBackground, ^bmpOrb, ^bmpTitle, ^bmpPlayRight, ^bmpPlayLeft;
		cGame *UNO;
		cPrintCards ^visualCard;
		Random r;

		short formState;
		short tempScore;
	public:
		GUI()
		{
			this->formState = 0;

			InitializeComponent();
			this->Buffer = BufferedGraphicsManager::Current->Allocate(this->CreateGraphics(), this->ClientRectangle);

			UNO = new cGame();

			this->bmpOrb = gcnew Bitmap("Assets//Orb.png");
			this->bmpLogo = gcnew Bitmap("Assets//Logo.png");
			this->bmpTitle = gcnew Bitmap("Assets//TitleCard.jpg");
			this->bmpPlayRight = gcnew Bitmap("Assets//PlayRight.png");
			this->bmpPlayLeft = gcnew Bitmap("Assets//PlayLeft.png");

			this->visualCard = gcnew cPrintCards(this->Buffer);

			this->bmpBackground = this->bmpTitle;

			this->changeStates();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>

		~GUI()
		{
			if (components)
			{
				delete components;
			}
			delete bmpLogo;
			delete bmpTitle;
			delete bmpPlayLeft;
			delete bmpPlayRight;
			delete UNO;
			delete visualCard;
		}

	private: System::Windows::Forms::Timer^  RefreshRate;
	private: System::Windows::Forms::Timer^  BeepBoop;
	private: System::ComponentModel::IContainer^  components;
	private: System::Drawing::Graphics^ _graphics;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::ListBox^  listBox3;
	private: System::Windows::Forms::ListBox^  listBox4;
	private: System::Windows::Forms::ListBox^  listBox5;
	private: System::Windows::Forms::ListBox^  listBox6;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->RefreshRate = (gcnew System::Windows::Forms::Timer(this->components));
			this->BeepBoop = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->listBox4 = (gcnew System::Windows::Forms::ListBox());
			this->listBox5 = (gcnew System::Windows::Forms::ListBox());
			this->listBox6 = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// RefreshRate
			// 
			this->RefreshRate->Enabled = true;
			this->RefreshRate->Interval = 16;
			this->RefreshRate->Tick += gcnew System::EventHandler(this, &GUI::RR_Tick);
			//
			// BeepBoop
			//
			this->BeepBoop->Enabled = true;
			this->BeepBoop->Interval = 1500;
			this->BeepBoop->Tick += gcnew System::EventHandler(this, &GUI::BotThinking);
			// 
			// button1
			// 
			this->button1->Name = L"button1";
			this->button1->TabIndex = 0;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &GUI::button1_Click);
			// 
			// button2
			// 
			this->button2->Name = L"button2";
			this->button2->TabIndex = 0;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &GUI::button2_Click);
			// 
			// button3
			// 
			this->button3->Name = L"button3";
			this->button3->TabIndex = 0;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &GUI::button3_Click);
			// 
			// button4
			// 
			this->button4->Name = L"button4";
			this->button4->TabIndex = 0;
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &GUI::button4_Click);
			// 
			// label1
			// 
			this->label1->Name = L"label1";
			this->label1->TabIndex = 0;
			// 
			// label2
			// 
			this->label2->Name = L"label2";
			this->label2->TabIndex = 0;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox1->Location = System::Drawing::Point(120, 100);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 520);
			this->listBox1->TabIndex = 0;
			this->listBox1->Items->Add(" Games");
			this->listBox1->Items->Add("======");
			this->listBox1->Items->Add("      1");
			this->listBox1->Items->Add("======");
			this->listBox1->Items->Add("      2");
			this->listBox1->Items->Add("======");
			this->listBox1->Items->Add("      3");
			this->listBox1->Items->Add("======");
			this->listBox1->Items->Add("      4");
			this->listBox1->Items->Add("======");
			this->listBox1->Items->Add("      5");
			this->listBox1->Items->Add("======");
			this->listBox1->Items->Add(" Total:");
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox2->Location = System::Drawing::Point(300, 100);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(120, 520);
			this->listBox2->TabIndex = 0;
			this->listBox2->Items->Add("   You");
			this->listBox2->Items->Add("======");
			this->listBox2->Items->Add("      -");
			this->listBox2->Items->Add("======");
			this->listBox2->Items->Add("      -");
			this->listBox2->Items->Add("======");
			this->listBox2->Items->Add("      -");
			this->listBox2->Items->Add("======");
			this->listBox2->Items->Add("      -");
			this->listBox2->Items->Add("======");
			this->listBox2->Items->Add("      -");
			this->listBox2->Items->Add("======");
			this->listBox2->Items->Add("      -");
			// 
			// listBox3
			// 
			this->listBox3->FormattingEnabled = true;
			this->listBox3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox3->Location = System::Drawing::Point(480, 100);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(120, 520);
			this->listBox3->TabIndex = 0;
			this->listBox3->Items->Add("  Elvia");
			this->listBox3->Items->Add("======");
			this->listBox3->Items->Add("      -");
			this->listBox3->Items->Add("======");
			this->listBox3->Items->Add("      -");
			this->listBox3->Items->Add("======");
			this->listBox3->Items->Add("      -");
			this->listBox3->Items->Add("======");
			this->listBox3->Items->Add("      -");
			this->listBox3->Items->Add("======");
			this->listBox3->Items->Add("      -");
			this->listBox3->Items->Add("======");
			this->listBox3->Items->Add("      -");
			// 
			// listBox4
			// 
			this->listBox4->FormattingEnabled = true;
			this->listBox4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox4->Location = System::Drawing::Point(660, 100);
			this->listBox4->Name = L"listBox4";
			this->listBox4->Size = System::Drawing::Size(120, 520);
			this->listBox4->TabIndex = 0;
			this->listBox4->Items->Add("  Diego");
			this->listBox4->Items->Add("======");
			this->listBox4->Items->Add("      -");
			this->listBox4->Items->Add("======");
			this->listBox4->Items->Add("      -");
			this->listBox4->Items->Add("======");
			this->listBox4->Items->Add("      -");
			this->listBox4->Items->Add("======");
			this->listBox4->Items->Add("      -");
			this->listBox4->Items->Add("======");
			this->listBox4->Items->Add("      -");
			this->listBox4->Items->Add("======");
			this->listBox4->Items->Add("      -");
			// 
			// listBox5
			// 
			this->listBox5->FormattingEnabled = true;
			this->listBox5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox5->Location = System::Drawing::Point(840, 100);
			this->listBox5->Name = L"listBox5";
			this->listBox5->Size = System::Drawing::Size(120, 520);
			this->listBox5->TabIndex = 0;
			this->listBox5->Items->Add("  Maria");
			this->listBox5->Items->Add("======");
			this->listBox5->Items->Add("      -");
			this->listBox5->Items->Add("======");
			this->listBox5->Items->Add("      -");
			this->listBox5->Items->Add("======");
			this->listBox5->Items->Add("      -");
			this->listBox5->Items->Add("======");
			this->listBox5->Items->Add("      -");
			this->listBox5->Items->Add("======");
			this->listBox5->Items->Add("      -");
			this->listBox5->Items->Add("======");
			this->listBox5->Items->Add("      -");
			// 
			// listBox6
			// 
			this->listBox6->FormattingEnabled = true;
			this->listBox6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox6->Location = System::Drawing::Point(1020, 100);
			this->listBox6->Name = L"listBox6";
			this->listBox6->Size = System::Drawing::Size(120, 520);
			this->listBox6->TabIndex = 0;
			this->listBox6->Items->Add("  Bryam");
			this->listBox6->Items->Add("======");
			this->listBox6->Items->Add("      -");
			this->listBox6->Items->Add("======");
			this->listBox6->Items->Add("      -");
			this->listBox6->Items->Add("======");
			this->listBox6->Items->Add("      -");
			this->listBox6->Items->Add("======");
			this->listBox6->Items->Add("      -");
			this->listBox6->Items->Add("======");
			this->listBox6->Items->Add("      -");
			this->listBox6->Items->Add("======");
			this->listBox6->Items->Add("      -");
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1280, 720);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"GUI";
			this->Text = L"UNO";
			this->Click += gcnew System::EventHandler(this, &GUI::MyForm_MouseDown);
			this->ResumeLayout(false);

		}

#pragma endregion

	private: System::Void RR_Tick(System::Object^  sender, System::EventArgs^  e) {

		if (this->UNO->Match) {
			if (this->UNO->Match->getDirection() == 1)
				this->Buffer->Graphics->DrawImage(this->bmpPlayRight, this->ClientRectangle);
			else this->Buffer->Graphics->DrawImage(this->bmpPlayLeft, this->ClientRectangle);

			Hovered();
			this->printOrb();
			this->visualCard->printDeck(this->UNO->Match->getDeckPosition());
			this->visualCard->printStack(this->UNO->Stack->back());
			this->printCards();
		}
		else {
			this->Buffer->Graphics->DrawImage(this->bmpBackground, this->ClientRectangle);
			if (formState == 1) {
				this->Buffer->Graphics->DrawImage(this->bmpLogo, Rectangle(clientWidth / 2 - bmpLogo->Width*0.8 / 1.25, clientHeight / 2 - bmpLogo->Height*0.8 / 2,
					bmpLogo->Width*0.8, bmpLogo->Height*0.8));
			}
		}

		this->Buffer->Render(this->CreateGraphics());
	}

	private: System::Void BotThinking(System::Object^  sender, System::EventArgs^  e) {
		if (this->formState == 2) {
			if (this->UNO->Match->getCurrentPlayer())
				for (short cardIndex = 0; cardIndex < this->UNO->Match->Players->at(this->UNO->Match->getCurrentPlayer())->Hand->size() + 1; cardIndex++) {
					if (cardIndex == this->UNO->Match->Players->at(this->UNO->Match->getCurrentPlayer())->Hand->size()) {
						this->UNO->Match->drawCard();
						if (this->UNO->Match->verifyPlay(this->UNO->Match->Players->at(this->UNO->Match->getCurrentPlayer())->Hand->back())) {
							this->UNO->Match->playCard(this->UNO->Match->Players->at(this->UNO->Match->getCurrentPlayer())->Hand->size() - 1);
							if (this->UNO->Match->usingTempColor) {
								this->UNO->Match->usingTempColor = false;
								this->Controls->Remove(this->label1);
							}
							if (this->UNO->Match->needColorPick) {
								this->UNO->Match->setTempColor(r.Next(0, 4));
								this->label1->Text = this->UNO->Match->getTempColor();
								this->Controls->Add(this->label1);
							}
						}
						else this->UNO->Match->nextTurn();
						break;
					}
					if (this->UNO->Match->verifyPlay(this->UNO->Match->Players->at(this->UNO->Match->getCurrentPlayer())->Hand->at(cardIndex))) {
						if (this->UNO->Match->playCard(cardIndex)) {
							this->formState = 4;
							this->changeStates();
							break;
						}
						if (this->UNO->Match->usingTempColor) {
							this->UNO->Match->usingTempColor = false;
							this->Controls->Remove(this->label1);
						}
						if (this->UNO->Match->needColorPick) {
							this->UNO->Match->setTempColor(r.Next(0, 4));
							this->label1->Text = this->UNO->Match->getTempColor();
							this->Controls->Add(this->label1);
						}
						break;
					}
				}
		}
	}

			 void Hovered() {
				 for (short cardIndex = this->UNO->Players->at(0)->Hand->size() - 1; cardIndex >= 0; cardIndex--) {
					 if (this->UNO->Players->at(0)->Hand->at(cardIndex)->getPosition().Contains(this->PointToClient(System::Windows::Forms::Cursor::Position))) {
						 this->UNO->Players->at(0)->Hand->at(cardIndex)->Hovered = true;
						 for (short otherCardIndex = cardIndex - 1; otherCardIndex >= 0; otherCardIndex--)
							 this->UNO->Players->at(0)->Hand->at(otherCardIndex)->Hovered = false;
						 break;
					 }
					 else this->UNO->Players->at(0)->Hand->at(cardIndex)->Hovered = false;
				 }
				 if (this->UNO->Match->getDeckPosition().Contains(this->PointToClient(System::Windows::Forms::Cursor::Position)))
					 this->UNO->Match->deckHovered = true;
				 else this->UNO->Match->deckHovered = false;
			 }

			 void printCards() {
				 for (short playerIndex = 0; playerIndex < this->UNO->Players->size(); playerIndex++)
					 for (short cardIndex = 0; cardIndex < this->UNO->Players->at(playerIndex)->Hand->size(); cardIndex++) {
						 this->UNO->Players->at(playerIndex)->Hand->at(cardIndex)->setPoint(this->UNO->Players->at(playerIndex)->getCenter(),
							 this->UNO->Players->at(playerIndex)->getHorizontal(), this->UNO->Players->at(playerIndex)->Hand->size(), cardIndex);
						 this->visualCard->printCard(this->UNO->Players->at(playerIndex)->Hand->at(cardIndex));
					 }
			 }

			 void printOrb() {
				 if (this->UNO->Players->at(this->UNO->Match->getCurrentPlayer())->getHorizontal())
					 this->Buffer->Graphics->DrawImage(bmpOrb, Rectangle(this->UNO->Players->at(this->UNO->Match->getCurrentPlayer())->getCenter().X - 70 * this->UNO->Players->at(this->UNO->Match->getCurrentPlayer())->Hand->size() / 2,
						 this->UNO->Players->at(this->UNO->Match->getCurrentPlayer())->getCenter().Y - 80,
						 70 * this->UNO->Players->at(this->UNO->Match->getCurrentPlayer())->Hand->size(), 160));
				 else
					 this->Buffer->Graphics->DrawImage(bmpOrb, Rectangle(this->UNO->Players->at(this->UNO->Match->getCurrentPlayer())->getCenter().X - (cardWidth + 40) / 2,
						 this->UNO->Players->at(this->UNO->Match->getCurrentPlayer())->getCenter().Y - (cardHeight + 5) * this->UNO->Players->at(this->UNO->Match->getCurrentPlayer())->Hand->size() / 2,
						 cardWidth + 40, (cardHeight + 5) * this->UNO->Players->at(this->UNO->Match->getCurrentPlayer())->Hand->size()));
			 }

			 void changeStates() {
				 switch (this->formState) {
				 case 0:
					 this->label1->Location = System::Drawing::Point(540, 272);
					 this->label1->Size = System::Drawing::Size(200, 52);
					 this->label1->Text = L"How many are Playing?";
					 this->label1->TabIndex = 2;
					 this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(0)));
					 this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 this->Controls->Add(this->label1);


					 this->button1->Location = System::Drawing::Point(505, 370);
					 this->button1->Size = System::Drawing::Size(74, 24);
					 this->button1->Text = L"3";
					 this->Controls->Add(this->button1);

					 this->button2->Location = System::Drawing::Point(603, 370);
					 this->button2->Size = System::Drawing::Size(74, 24);
					 this->button2->Text = L"4";
					 this->Controls->Add(this->button2);

					 this->button3->Location = System::Drawing::Point(701, 370);
					 this->button3->Size = System::Drawing::Size(74, 24);
					 this->button3->Text = L"5";
					 this->Controls->Add(this->button3);

					 this->Controls->Remove(this->button4);
					 break;

				 case 1:
					 this->Controls->Remove(this->label1);

					 this->button1->Location = System::Drawing::Point(750, 312);
					 this->button1->Size = System::Drawing::Size(100, 24);
					 this->button1->Text = L"Play Game";

					 this->button2->Location = System::Drawing::Point(750, 348);
					 this->button2->Size = System::Drawing::Size(100, 24);
					 this->button2->Text = L"ScoreBoard";
					 this->Controls->Add(this->button2);

					 this->button3->Location = System::Drawing::Point(750, 384);
					 this->button3->Size = System::Drawing::Size(100, 24);
					 this->button3->Text = L"Back";
					 this->Controls->Add(this->button3);

					 this->Controls->Remove(this->button4);
								 this->Controls->Remove(this->listBox1);
								 this->Controls->Remove(this->listBox2);
								 this->Controls->Remove(this->listBox3);
								 this->Controls->Remove(this->listBox4);
								 this->Controls->Remove(this->listBox5);
								 this->Controls->Remove(this->listBox6);
					 break;

				 case 2:
					 this->label1->Location = System::Drawing::Point(603, 360 + cardHeight / 2 + 12);
					 this->label1->Size = System::Drawing::Size(74, 24);
					 this->label1->TabIndex = 1;
					 this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(0)));
					 this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 this->Controls->Remove(this->label1);

					 this->button1->Location = System::Drawing::Point(175, 680 - 24);
					 this->button1->Size = System::Drawing::Size(100, 24);
					 this->button1->Text = L"Sneak Peek";
					 this->Controls->Add(this->button1);
					 if (!this->UNO->Match->cheatQT)
						 this->Controls->Remove(this->button1);




					 this->Controls->Remove(this->button2);
					 this->Controls->Remove(this->button3);
					 this->Controls->Remove(this->button4);

					 break;

				 case 3:
					 this->button1->Location = System::Drawing::Point(554, 324);
					 this->button1->Size = System::Drawing::Size(74, 24);
					 this->button1->Text = L"Red";
					 this->Controls->Add(this->button1);

					 this->button2->Location = System::Drawing::Point(652, 324);
					 this->button2->Size = System::Drawing::Size(74, 24);
					 this->button2->Text = L"Yellow";
					 this->Controls->Add(this->button2);

					 this->button3->Location = System::Drawing::Point(554, 372);
					 this->button3->Size = System::Drawing::Size(74, 24);
					 this->button3->Text = L"Blue";
					 this->Controls->Add(this->button3);

					 this->button4->Location = System::Drawing::Point(652, 372);
					 this->button4->Size = System::Drawing::Size(74, 24);
					 this->button4->Text = L"Green";
					 this->Controls->Add(this->button4);
					 break;

				 case 4:
					 this->label1->Location = System::Drawing::Point(570, 300);
					 this->label1->Size = System::Drawing::Size(140, 48);
					 this->label1->TabIndex = 2;
					 this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(0)));
					 this->label1->Text = this->UNO->Match->getWinner();
					 this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 this->Controls->Add(this->label1);

					 this->button1->Location = System::Drawing::Point(603, 372);
					 this->button1->Size = System::Drawing::Size(74, 24);
					 this->button1->Text = L"Got it!";
					 this->Controls->Add(this->button1);


					 this->Controls->Remove(this->button2);
					 this->Controls->Remove(this->button3);
					 this->Controls->Remove(this->button4);
					 break;
				 case 5:
					 if (this->UNO->Players->at(0)->score.size())
						 for (short playerIndex = 0; playerIndex < this->UNO->Players->size(); playerIndex++) {
							 tempScore = 0;
							 for (short scoreIndex = 1; scoreIndex <= this->UNO->Players->at(playerIndex)->score.size(); scoreIndex++) {
								 tempScore += this->UNO->Players->at(playerIndex)->score.at(scoreIndex - 1);
								 switch (playerIndex) {
								 case 0:
									 this->listBox2->Items->RemoveAt(2 * scoreIndex);
									 this->listBox2->Items->Insert(2 * scoreIndex, Convert::ToString(this->UNO->Players->at(playerIndex)->score.at(scoreIndex - 1)));
									 this->listBox2->Items->RemoveAt(12);
									 this->listBox2->Items->Add(Convert::ToString(tempScore));
									 break;
								 case 1:
									 this->listBox3->Items->RemoveAt(2 * scoreIndex);
									 this->listBox3->Items->Insert(2 * scoreIndex, Convert::ToString(this->UNO->Players->at(playerIndex)->score.at(scoreIndex - 1)));
									 this->listBox3->Items->RemoveAt(12);
									 this->listBox3->Items->Add(Convert::ToString(tempScore));
									 break;
								 case 2:
									 this->listBox4->Items->RemoveAt(2 * scoreIndex);
									 this->listBox4->Items->Insert(2 * scoreIndex, Convert::ToString(this->UNO->Players->at(playerIndex)->score.at(scoreIndex - 1)));
									 this->listBox4->Items->RemoveAt(12);
									 this->listBox4->Items->Add(Convert::ToString(tempScore));
									 break;
								 case 3:
									 this->listBox5->Items->RemoveAt(2 * scoreIndex);
									 this->listBox5->Items->Insert(2 * scoreIndex, Convert::ToString(this->UNO->Players->at(playerIndex)->score.at(scoreIndex - 1)));
									 this->listBox5->Items->RemoveAt(12);
									 this->listBox5->Items->Add(Convert::ToString(tempScore));
									 break;
								 case 4:
									 this->listBox6->Items->RemoveAt(2 * scoreIndex);
									 this->listBox6->Items->Insert(2 * scoreIndex, Convert::ToString(this->UNO->Players->at(playerIndex)->score.at(scoreIndex - 1)));
									 this->listBox6->Items->RemoveAt(12);
									 this->listBox6->Items->Add(Convert::ToString(tempScore));
									 break;
								 }
							 }
						 }
					 this->Controls->Add(this->listBox1);
					 this->Controls->Add(this->listBox2);
					 this->Controls->Add(this->listBox3);
					 this->Controls->Add(this->listBox4);
					 switch (this->UNO->Players->size()) {
					 case 4: this->Controls->Add(this->listBox5); break;
					 case 5: this->Controls->Add(this->listBox5); this->Controls->Add(this->listBox6); break;
					 default: break;
					 }
					 this->button1->Location = System::Drawing::Point(50, 50);
					 this->button1->Size = System::Drawing::Size(48, 24);
					 this->button1->Text = L"<<";
					 this->Controls->Add(this->button1);
					
					 this->Controls->Remove(this->button2);
					 this->Controls->Remove(this->button3);
					 this->Controls->Remove(this->button4);
					 break;
				 }
			 }

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		switch (formState) {
		case 0:
			this->UNO->addPlayers(3);
			this->formState = 1;
			this->changeStates();
			break;
		case 1:
			this->UNO->startMatch();
			this->formState = 2;
			this->changeStates();
			break;
		case 2:
			this->UNO->Match->tryCheat = true;
			break;
		case 3:
			this->UNO->Match->setTempColor(Red);
			this->formState = 2;
			this->changeStates();
			this->label1->Text = this->UNO->Match->getTempColor();
			this->Controls->Add(this->label1);
			break;
		case 4:
			this->UNO->endMatch();
			this->formState = 1;
			this->changeStates();
			this->Controls->Remove(this->button3);
			break;
		case 5:
			this->formState = 1;
			this->changeStates();
			if (this->UNO->Players->at(0)->score.size())
				this->Controls->Remove(this->button3);
			break;
		}
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		switch (formState) {
		case 0:
			this->UNO->addPlayers(4);
			this->formState = 1;
			this->changeStates();
			break;
		case 1:
			this->formState = 5;
			this->changeStates();
			break;
		case 3:
			this->UNO->Match->setTempColor(Yellow);
			this->formState = 2;
			this->changeStates();
			this->label1->Text = this->UNO->Match->getTempColor();
			this->Controls->Add(this->label1);
			break;
		}
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		switch (formState) {
		case 0:
			this->UNO->addPlayers(5);
			this->formState = 1;
			this->changeStates();
			break;

		case 1:
			this->UNO->removePlayers();
			this->formState = 0;
			this->changeStates();
			break;

		case 3:
			this->UNO->Match->setTempColor(Blue);
			this->formState = 2;
			this->changeStates();
			this->label1->Text = this->UNO->Match->getTempColor();
			this->Controls->Add(this->label1);
			break;
		}
	}

	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		switch (formState) {
		case 3:
			this->UNO->Match->setTempColor(Green);
			this->formState = 2;
			this->changeStates();
			this->label1->Text = this->UNO->Match->getTempColor();
			this->Controls->Add(this->label1);
			break;
		}
	}

	private: System::Void MyForm_MouseDown(System::Object^  sender, System::EventArgs^  e) {
		if (this->formState == 2) {
			if (!this->UNO->Match->getCurrentPlayer()) {
				for (short cardIndex = 0; cardIndex < this->UNO->Players->at(0)->Hand->size(); cardIndex++)
					if (this->UNO->Players->at(0)->Hand->at(cardIndex)->Hovered)
						if (this->UNO->Match->verifyPlay(this->UNO->Players->at(0)->Hand->at(cardIndex))) {
							if (this->UNO->Match->playCard(cardIndex)) {
								this->formState = 4;
								this->changeStates();
								break;
							}
							if (this->UNO->Match->usingTempColor) {
								this->UNO->Match->usingTempColor = false;
								this->Controls->Remove(this->label1);
							}
							if (this->UNO->Match->needColorPick) {
								this->formState = 3;
								this->changeStates();
							}
						}
			}
			if (this->formState == 2) {
				if (this->UNO->Match->deckHovered) {
					this->UNO->Match->drawCard();
					if (this->UNO->Match->verifyPlay(this->UNO->Match->Players->at(0)->Hand->back())) {
						this->UNO->Match->playCard(this->UNO->Match->Players->at(0)->Hand->size() - 1);
						if (this->UNO->Match->usingTempColor) {
							this->UNO->Match->usingTempColor = false;
							this->Controls->Remove(this->label1);
						}
						if (this->UNO->Match->needColorPick) {
							this->formState = 3;
							this->changeStates();
						}
					}
					else this->UNO->Match->nextTurn();
				}
				if (this->UNO->Match->tryCheat) {
					if (!this->UNO->Match->cheat(this->PointToClient(System::Windows::Forms::Cursor::Position)))
						this->Controls->Remove(this->button1);
					this->UNO->Match->tryCheat = false;
				}
			}
		}
	}
	};
}