# ControlLedButton
Здесь реализован скетч для Arduino nano который управляет яркостью светодиодной ленты.
К Arduino подключена тактовая кнопка и транзистор управляющий светодиодной лентой.
Реализовано три режима работы :
  0. лента выключена
  1. устанавливает яркость примерно на 60%
  2. устанавливает яркость примерно на 30%
также при удерживании кнопки лента плавно разгорается до максимума и гаснет. это сделано
чтобы можно было сразу выключить ленту из любого режима.
Также изминения яркости происходит плавно за счет этого создается прятный визуальный эффект.