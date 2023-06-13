#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include <chrono>
#include <thread>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using namespace sf;
using namespace std::chrono;

//—оздайте класс AnimatedText, который позволит создавать анимированный вывод текста. ласс должен содержать строку text и переменную duration, котора€ указывает врем€ вывода всей строки на экран.
//ѕродемонстрируйте его работу при помощи SFML.
//ѕример работы класса :
//«адана строка Hello, world!и врем€ вывода 13 секунд.¬ первую секунду по€витс€ буква H, во вторую Ц He, далее Hel и т.д. ажда€ буква по€вл€етс€ через равный промежуток времени.
//ѕожелани€ к реализации :
//-используйте константные ссылки, где в этом есть потребность.
//
//- пометьте соответствующие методы ключевым словом const.
//
//- подумайте, как сделать так, чтобы AnimatedText был не прив€зан к одной графической библиотеке.“о есть разделена логика работы и отображение.

class AnimatedText
{
private:
	string m_str;
	string help_str{ " " };
	int m_duration;
	int m_i = 1;
	std::chrono::milliseconds m_nexttime;
	std::chrono::milliseconds m_now;
	std::chrono::milliseconds m_start;
	bool m_Started = false;
public:
	AnimatedText(const string& str, int duration)
	{
		m_str = str;
		m_duration = duration;
		m_nexttime = (std::chrono::milliseconds)(duration *100 / str.length());
	}
	void Animate()
	{
		if (m_i >= m_str.length())
			return;
		if (!m_Started)
		{
			m_start = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch() / 10);
			help_str[0] = m_str[0];
			m_Started = true;
		}

		m_now = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch() / 10);

		if ((m_now - m_start) == m_nexttime)
		{
			m_start += m_nexttime;
			help_str += m_str[m_i];
			m_i++;
		}
	}
	string strret()
	{
		return help_str;
	}
};




int main()
{
	string string1;
	getline(cin, string1);
	double time;
	cin >> time;

	AnimatedText example(string1, time);


	Font arial;
	if (!arial.loadFromFile("fonts/arial.ttf"))
	{
		cout << "Font load error" << endl;

	}
	Text text;
	text.setFont(arial);
	text.setFillColor(Color::Red);

	RenderWindow window(VideoMode(200, 200), "Animated Text");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		example.Animate();
		text.setString(example.strret());
		window.clear();
		window.draw(text);
		window.display();

	}
	return 0;
}