7 VIÊN BI RỒNG

Tên game ("7 viên bi rồng")

Điều khiển: Sử dụng WASD để di chuyển, phím space để bắn (bao gồm Kamehameha)
Mục tiêu: Tiêu diệt kẻ thù (20 con, di chuyển ngẫu nhiên, bắn đạn laser), thu thập tiền (PlayerMoney), và đạt điểm cao (mark_value).
Giao diện game:
![image](https://github.com/user-attachments/assets/ea0d76ba-2176-4e6d-9af5-0c63f267df08)

Hệ thống mạng sống (PlayerPower, tối đa 3 lần chết).
Đạn và vũ khí: Goku bắn đạn, có thể dùng Kamehameha.
Kẻ thù: Di chuyển linh hoạt, bắn đạn laser, va chạm gây mất mạng.
Hiệu ứng: Vụ nổ (exp3.png) khi kẻ thù hoặc Goku bị tiêu diệt.
Thời gian: Giới hạn 300 giây, hết thời gian game kết thúc.
Cấp độ: Hiện tại có một bản đồ (map01.dat), nhưng có tiềm năng mở rộng.

Công cụ: Game dùng C++ với SDL2, SDL_image, SDL_ttf, SDL_mixer để xử lý đồ họa, văn bản, và âm thanh.
Tài nguyên: Hình ảnh (Goku, kẻ thù, vụ nổ), âm thanh (súng, Kamehameha, nổ), và font chữ (dlxfont, Haverbrooke, Keylock Fighter).
Xử lý va chạm giữa đạn, kẻ thù, và người chơi (dùng SDLCommonFunc::CheckCollision).

