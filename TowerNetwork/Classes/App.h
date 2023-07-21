#pragma once

/// @file App.h
/// @brief Файл класса управления
/// @details Содержит класс, который управляет 

#include "Signal.h"
#include "Tower.h"
#include "TowerNetwork.h"
#include "Command.h"

/// @brief Пространство имен проекта
namespace ntw {

	/**
	 * @brief Управляющий класс
	 * @details По странным стечениям обстоятельств, назвал его
	 * "приложение". Не знаю, полчему так. По сути это - исполняющее
	 * команды "ядро".
	 * 
	 * В настоящее время для логирования статично зашит стандартный поток
	 * ввода-вывода
	*/
	class App
	{
	public:
		~App();

	private:
		
	private:
		/// @brief Указатель на сеть
		TowerNetwork* network;

		/// @brief Указатель на текущую выбранную башню
		Tower* pCurrentSelection = nullptr;

		/// @brief Номер текущей выбранной башни
		/// @details Служит для упрощения читаемости кода
		int curTower = -1;

		/// @brief Мтод иницилизации
		/// @return Успешность выполнения
		bool init();

		/// @brief Метод ввода команды
		/// @return Обработанная команда
		IntCom inputComand();		

		/// @brief Метод выполнения команды
		/// @param com Команда, которую нужно выполнить
		void completeCommand(IntCom& com);

	public:
		/// @brief Метод запуска
		/// @return Код завершения
		int Run();

	};

}



