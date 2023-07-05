#pragma once

/// @file TowerNetwork.h
/// @brief

#include <map>

/// @brief Пространство имен проекта
namespace ntw {

	class Tower;

	/**
	 * @brief Класс сети башен
	 * @details Содержит в себе контейнер башен (которые могут быть
	 * соеденены или нет), контролирует их создание, присваение
	 * уникальных номеров.
	*/
	class TowerNetwork
	{
	public:
		TowerNetwork();
		~TowerNetwork() = default;

	private:
		//int CurrentTowers = 0;

		/// @brief Следующий уникальный номер
		static int NextTowerNumber;

		/// @brief Контейнер хранимых башен
		std::map<int, Tower*> Towers;

	public:
		/// @brief Метод создания башни
		/// @return Созданная башня
		Tower* CreateTower();

		/// @brief Метод получения башни по её номеру
		/// @param nTower Номер башни
		/// @return Башня
		Tower* GetTowerByNumber(int nTower);

		/// @brief Метод получения башни по номеру в массиве
		/// @param n Номер в массиве
		/// @return Башня
		Tower* GetTower(int n);

		/// @brief Метод соединения башен
		/// @param nSender Башня - источник сигнала
		/// @param nListener Башня - слушатель
		/// @deprecated
		void ConnectTowers(int nSender, int nListener);

	};

}

