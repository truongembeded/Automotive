/* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;// CAN_TTCM là tạo thời gian bao nhiêu time đó nó sẽ gửi bit 1 lần
    CAN_InitStructure.CAN_ABOM = DISABLE;//CAN_ABOM là khi trong quá trình send data bi lỗi thì nó will return nó send again khi enable
					//còn disable thì nó không cố gắng send data tiếp theo mà nó stop lai và send bit tiếp theo
    CAN_InitStructure.CAN_AWUM = DISABLE;// mode sleep khi send data nó sẽ thức dậy khi disable là không cho nó vào mode sleep
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;// CAN_RFLM is mode first in first out same queue in c
    CAN_InitStructure.CAN_TXFP = DISABLE;// disable is it priority id low thì send trước còn enable thì id nào có trước thì truyền trước
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//có all 4 mode khi set up mode này thì có thể truyền nhận bình thường
		//CAN_Mode_LookBack : mode này khi set up mình gửi data di nó sẽ lưu vào bộ nhớ đệm khi send data đi thì có thể đọc lại nó
		//CAN_Mode_Silent : mode này just nhận data của vdk khác truyền về thôi
		//CAN_Mode_Silent_LookBack : mode này có thể xem lại data mình send trước đó có đúng hay không, mode này dùng để debug xem data truyền nhận có giống nhau không
		
    /* CAN Baudrate = 8MBps*/									// 1(8/4) = 0.5 micro giay
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;//Khoảng thời gian tối thiểu mà tín hiệu truyền dữ liệu được phép trễ so với tín hiệu đồng bộ hóa trong chu kỳ truyền dữ liệu
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;// độ trể thời gian đầu mà tín hiệu gửi đi 1 bit trong quá trình truyền
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;// độ trể thời gian cuối mà tín hiệu gửi đi 1 bit trong quá trình truyền
    CAN_InitStructure.CAN_Prescaler = 4; // time quanta là time send 1 bit 
    CAN_Init(CAN1, &CAN_InitStructure);

    CAN_FilterInitStructure.CAN_FilterNumber = 0;// bộ lọc để lọc id thường sẽ set up = 0
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;// khi truyền data mà id truyền và id nhận bằng nhau thì nó sẽ cho phép nhận data
					     CAN_FillterMode_IdList;// nó sẽ cho phép lưu được nhiều id khi mình muốn nhận data từ nhiều id khác nhau
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = can_id;// khởi tạo ban đầu cho nó vì truyền nó không liên quan đến, khi nhận mới cần set up cho nó
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;// này củng vậy

	Mặt nạ được sử dụng để xác định (& bit) bit nào trong địa chỉ ID cần được so sánh 
	và những bit nào nên được bỏ qua trong quá trình lọc
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0xFFFF;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;// chế độ để sử dụng FIFO0 hay FIFO1
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;// kích hoạt thông số của bộ lọc phía trên
    CAN_FilterInit(&CAN_FilterInitStructure);
}