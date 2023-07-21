#pragma once

/// @file TowerNode.h
/// @brief Файл с классом узла

#include <vector>
#include "TowerSize.h"

/// @brief Пространство имен проекта
namespace ntw {

    /**
     * @brief Пространство абстракций
     * @details Специальное пространство имен для абстрактных понятий,
     * но не факт, что абсолютно все тут будет являтся абстрактным 
     * классом.
    */
    namespace abstr {

        /**
         * @brief Класс узла башни в сети связи
         * @details Является скелетом сети свзи. Отвечает за
         * установление, получение, разрыв связи между башнями.
        */
        class TowerNode
        {
        public:
            TowerNode();
            TowerNode(const TowerNode& src);
            TowerNode(TowerNode&& from) noexcept;
            
            /// @brief Конструктор с параметрами
            /// @param size Размер - лимит подключений
            TowerNode(const TowerSize& size);

            virtual ~TowerNode();

            TowerNode& operator=(const TowerNode& src);
            TowerNode& operator=(TowerNode&& from) noexcept;

            /// @brief Тип итератора для ориентирование в связях
            typedef std::vector<TowerNode*>::iterator Iterator;

        private:
            /// @brief Связанные ноды
            /// @details "Подписчики", которым башня рассылает сообщение
            std::vector<TowerNode*> ConnectedSubs;

            int maxSize; ///< Максимальный размер

        protected:
            /// @brief Метод добавления соединения
            /// @param pNode Башня, которая добавится
            /// @return Код ошибки
            int addConnect(TowerNode* pNode);

            /// @brief Метод разрыва соединения
            /// @param pNode Башня, с которой разрываем соединение
            /// @return Код ошибки
            int removeConnect(TowerNode* pNode);

            /// @brief Метод разрыва соединения по номеру соединения
            /// @param nConnection Номер соединения
            /// @return Код ошибки
            /// @overload
            int removeConnect(int nConnection);

            /// @brief Метод для разрыва последнего добавленного соединения
            void removeLastConnect();

            /// @brief Метод получения итератора на первое соединение
            /// @return Итератор на первую башню
            Iterator Begin() noexcept;

            /// @brief Метод получения итератора на конец соединений
            /// @return Итератор на конец списка соединений
            Iterator End() noexcept;

            /// @brief Метод проверки наличия соединения с башней
            /// @param pTower Башня, соединение с которой проверяем
            /// @return Наличие соединения
            bool isConnected(TowerNode* pTower);

            /// @brief Метод поиска соединения с башней
            /// @param pTower Башня, соединение с которой ищем
            /// @param seekIterator Итератор, который будет указывать на башю в соединениях
            /// @return Наличие соединения
            /// @overload
            bool isConnected(TowerNode* pTower, Iterator& seekIterator);

        public:
            /// @brief Метод для получения количества подсоединенных башен
            /// @return Количество "слуштелей"
            int getConnectedCount() const noexcept;

            /// @brief Метод получения лимита подключений
            /// @return Максимальное число подключений
            int getConnectedLimit() const noexcept;

            /// @brief Метод получения башни по номеру соединения
            /// @param nConnection Номер в списке соединений
            /// @return Башня, с которой установлена связь
            TowerNode* getAt(int nConnection);

        };

    }

}



