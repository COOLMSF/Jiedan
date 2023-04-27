
train_parameters = {
    "model_dir":"model/"     ,              # 模型路径
    "target_path": './data/faces/',         # 数据
    "train_path": './train.txt',            # train.txt路径
    "test_path": './test.txt',              # test.txt路径
    "readme_path": './readme.json',         # readme.json路径
    "label_dict": {},                       # 标签字典
    "num_epochs": 100,                        # 训练迭代次数
    "train_batch_size": 32,                  # 训练时每次喂入批次大小
    "learning_strategy": {                  # 优化时相关参数配置
        "lr": 0.01                         # 学习率
    }
}
