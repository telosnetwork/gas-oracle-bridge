module.exports = async ({getNamedAccounts, deployments}) => {

    const {deploy} = deployments;
    const {deployer} = await getNamedAccounts();
    const provider = ethers.getDefaultProvider();
    const feeData = await provider.getFeeData()
    const bridge = await deploy('GasOracleBridge', {
        from: deployer,
        args: [deployer, feeData.gasPrice],
    });

    console.log("Bridge deployed to:", bridge.address);

};
module.exports.tags = ['GasOracleBridge'];