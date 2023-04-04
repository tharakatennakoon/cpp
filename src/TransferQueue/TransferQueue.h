class TransferQueue
{
public:
    TransferQueue() = default;
    ~TransferQueue() = default;

    TransferQueue(const TransferQueue &) = default;
    TransferQueue(TransferQueue &&) = default;
    TransferQueue &operator=(const TransferQueue &) = default;
    TransferQueue &operator=(TransferQueue &&) = default;
};