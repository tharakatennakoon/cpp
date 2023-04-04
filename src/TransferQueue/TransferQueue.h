class TransferQueue
{
public:
    TransferQueue() = default;
    ~TransferQueue() = default;

    TransferQueue(TransferQueue &) = delete;
    TransferQueue(TransferQueue &&) = delete;
    TransferQueue &operator=(const TransferQueue &) = delete;
    TransferQueue &operator=(const TransferQueue &&) = delete;
};