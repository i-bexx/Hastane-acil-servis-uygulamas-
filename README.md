# Hastane-acil-servis-uygulaması-

1. Projenin Tanımı
Bu proje, hastanelerde acil servis hasta yönetimini sağlayan bir sistemdir. Hastaların kayıtlarını HL7 standardına uygun olarak saklar ve öncelik sırasına göre işlemlerini yürütür.

2. Kapsam
Hasta kayıtlarının oluşturulması
Acil servis kuyruğunda öncelik sırasına göre hasta yönetimi
Hastaya ilaç reçete numarası verilmesi
Hastanın işlenmesi (muayene, reçete yazımı, sistemden çıkarılması)
Kuyruğun görüntülenmesi ve yok edilmesi
3. Kullanılan Veri Yapıları
Struct: Hasta bilgilerini tutmak için kullanıldı.
Union: Sigorta numarası veya acil durum kişisini saklamak için kullanıldı.
Bağlı Liste (Linked List) ile Kuyruk (Queue): Hastaların öncelik sırasına göre kuyruğa eklenmesi sağlandı.
4. İşleyiş Akışı
Hasta bilgileri kaydedilir.
Hastanın önceliğine göre kuyrukta sıralanır.
Hasta işlendiğinde kuyruktan çıkarılır.
Hasta ve ilaç bilgileri görüntülenebilir.
Sistem kapatıldığında kuyruk temizlenir.
5. Kullanılan Fonksiyonlar
initQueue(): Kuyruğu başlatır.
enqueue(): Hastayı öncelik sırasına göre kuyruğa ekler.
dequeue(): En yüksek öncelikli hastayı işleyip çıkarır.
displayQueue(): Mevcut kuyruktaki hastaları gösterir.
destroyQueue(): Bellek sızıntısını önlemek için kuyruğu temizler.
